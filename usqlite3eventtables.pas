unit uSqlite3EventTables;

{$mode delphi}{$H+}

interface

uses
  Classes, SysUtils, uSqlite3Helper, sqlite3dyn, usqlite3virtualTable
  {$ifdef WINDOWS}
    {$I windows_units.inc}
  {$endif}
  ;

type

  { TEventCursor }

  TEventCursor = class(TSQLiteVirtualTableCursor)
  private
    FEof : Boolean;
    {$ifdef WINDOWS}
      {$I windows_cursorvars.inc}
    {$endif}
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

{$ifdef WINDOWS}
  {$I windows_implementation.inc}
{$endif}

end.

