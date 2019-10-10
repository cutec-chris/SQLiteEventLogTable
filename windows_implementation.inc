const
  wbemFlagForwardOnly = $00000020;
var
  fModule: TSQLite3Module;

{ TEventTable }

function TEventTable.Prepare(var Prepared: TSQLVirtualTablePrepared): Boolean;
var
  i: Integer;
  aPrep: PSQLVirtualTablePreparedConstraint;
begin
  for i := 0 to Prepared.WhereCount-1 do
    begin
      aPrep := @Prepared.Where[i];
      aPrep^.Value.VType := ftNull;
    end;
  Result := True;
end;

function TEventTable.GetName: string;
begin
  Result := 'event';
end;

function TEventTable.CursorClass: TSQLiteVirtualTableCursorClass;
begin
  Result := TEventCursor;
end;

function TEventTable.GenerateStructure: string;
const
  Structure = 'create table events ('+
  'Category  text,'+
  'ComputerName  text,'+
  'EventCode int,'+
  'Message  text,'+
  'RecordNumber  int'+
  ')';
begin
  Result := Structure;
end;


function GetWMIObject(const objectName: String): IDispatch; //create the Wmi instance
var
  chEaten: ^Cardinal;
  BindCtx: IBindCtx;
  Moniker: IMoniker;
begin
  OleCheck(CreateBindCtx(0, bindCtx));
  OleCheck(MkParseDisplayName(BindCtx, StringToOleStr(objectName), chEaten, Moniker));
  OleCheck(Moniker.BindToObject(BindCtx, nil, IDispatch, Result));
end;

{ TEventCursor }

function TEventCursor.Search(Prepared: TSQLVirtualTablePrepared): Boolean;
var
  i: Integer;
  aPrep: PSQLVirtualTablePreparedConstraint;
  tmp: PUTF8Char;
begin
  Result := True;
  try
//    FSWbemLocator := CreateOleObject('WbemScripting.SWbemLocator');
    FWMIService := GetWMIObject('winmgmts:\\localhost\root\CIMV2');
    //FWMIService   := FSWbemLocator.ConnectServer('localhost', 'root\CIMV2', '', '');
    for i := 0 to Prepared.WhereCount-1 do
      begin
      end;
    FWbemObjectSet:= FWMIService.ExecQuery('SELECT Category,ComputerName,EventCode,Message,RecordNumber FROM Win32_NTLogEvent  Where Logfile="System"','WQL',wbemFlagForwardOnly);
    oEnum         := IUnknown(FWbemObjectSet._NewEnum) as IEnumVariant;
    FEof := oEnum.Next(1, FWbemObject, {$IF FPC_FULLVERSION<=20604}@iValue{$ELSE}iValue{$ENDIF}) <> 0;
  except
    Result := False;
  end;
end;

function TEventCursor.Column(Index: Integer; var Res: TSQLVar): Boolean;
begin
  Result := False;
  try
    Res.VType:=ftNull;
    case Index of
    //-1:Res := Fsr.Time;
    0:begin
        Res.VType:=ftUTF8;
        Res.VText:= PUTF8Char(String(FWbemObject.Category));
      end;
    1:begin
        Res.VType:=ftUTF8;
        Res.VText:=PUTF8Char(String(FWbemObject.ComputerName));
      end;
    2:begin
        Res.VType:=ftInt64;
        Res.VInt64:= Integer(FWbemObject.EventCode);
      end;
    3:begin
        Res.VType:=ftUTF8;
        Res.VText:=PUTF8Char(String(FWbemObject.Message));
      end;
    4:begin
        Res.VType:=ftInt64;
        Res.VInt64:=Integer(FWbemObject.RecordNumber); //mtime
      end;
    end;
  except
  end;
  FWbemObject:=Unassigned;
  Result := True;
end;

function TEventCursor.Next: Boolean;
begin
  FEof := oEnum.Next(1, FWbemObject, {$IF FPC_FULLVERSION<=20604}@iValue{$ELSE}iValue{$ENDIF}) <> 0;
  Result := True;
end;

function TEventCursor.Eof: Boolean;
begin
  result := FEof;
end;

initialization
  CoInitialize(nil);
finalization
  CoUninitialize;
