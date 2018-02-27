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

{ TEventCursor }

function TEventCursor.Search(Prepared: TSQLVirtualTablePrepared): Boolean;
var
  i: Integer;
  aPrep: PSQLVirtualTablePreparedConstraint;
  tmp: PUTF8Char;
begin
  Result := True;
  for i := 0 to Prepared.WhereCount-1 do
    begin
    end;
end;

function TEventCursor.Column(Index: Integer; var Res: TSQLVar): Boolean;
begin
  Res.VType:=ftNull;
  case Index of
  //-1:Res := Fsr.Time;
  0:begin
      Res.VType:=ftUTF8;
    end;
  1:begin
      Res.VType:=ftUTF8;
    end;
  2:begin
      Res.VType:=ftInt64;
    end;
  3:begin
      Res.VType:=ftUTF8;
    end;
  4:begin
      Res.VType:=ftInt64;
    end;
  end;
  Result := True;
end;

function TEventCursor.Next: Boolean;
begin
  //FEof := oEnum.Next(1, FWbemObject, @iValue) <> 0;
  Result := True;
end;

function TEventCursor.Eof: Boolean;
begin
  result := FEof;
end;

initialization
finalization
