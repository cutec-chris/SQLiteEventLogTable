unit uSqlite3EventTables;

{$mode delphi}{$H+}

interface

uses
  Classes, SysUtils, uSqlite3Helper, sqlite3dyn, usqlite3virtualTable, ActiveX,
  ComObj, Variants;

type

  { TEventCursor }

  TEventCursor = class(TSQLiteVirtualTableCursor)
  private
    FEof : Boolean;
  public
    function Search(Prepared : TSQLVirtualTablePrepared) : Boolean;override;
    function Column(Index : Integer;var Res : TSQLVar) : Boolean;override;
    function Next : Boolean;override;
    function Eof : Boolean;override;
  end;

  TEventCursorClass = class of TEventCursor;

  { TEventTable }

  TEventTable = class(TSQLiteVirtualTable)
  public
    function Prepare(var Prepared: TSQLVirtualTablePrepared): Boolean; override;
    function GetName: string; override;
    function CursorClass: TSQLiteVirtualTableCursorClass; override;
    function GenerateStructure: string; override;
  end;

implementation

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
  'name  text,'+
  'path  text,'+
  'isdir int,'+
  'size  int,'+
  'time  date'+
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
{
  case Index of
  //-1:Res := Fsr.Time;
  0:begin
      Res.VType:=ftUTF8;
      Res.VText:= PUTF8Char(FSearchRecs[length(FSearchRecs)-1].Name);//name
    end;
  1:begin
      Res.VType:=ftUTF8;
      Res.VText:=PUTF8Char(FPath);//path
    end;
  2:begin
      Res.VType:=ftInt64;
      if FSearchRecs[length(FSearchRecs)-1].Attr and faDirectory = faDirectory then
        Res.VInt64:= 1
      else
        Res.VInt64:= 0; //isdir
    end;
  3:begin
      Res.VType:=ftInt64;
      Res.VInt64 := FSearchRecs[length(FSearchRecs)-1].Size;//size
    end;
  4:begin
      Res.VType:=ftDate;
      Res.VDateTime:=FileDateToDateTime(FSearchRecs[length(FSearchRecs)-1].Time); //mtime
    end;
  //ctime
  //atime
  end;
}
  Result := True;
end;

function TEventCursor.Next: Boolean;
label retry;
begin
  Result := True;
end;

function TEventCursor.Eof: Boolean;
begin
  result := FEof;
end;

end.

