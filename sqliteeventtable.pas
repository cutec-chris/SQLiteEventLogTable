{ This file was automatically created by Lazarus. Do not edit!
  This source is only used to compile and install the package.
 }

unit sqliteeventtable;

interface

uses
  uSqlite3EventTables, LazarusPackageIntf;

implementation

procedure Register;
begin
end;

initialization
  RegisterPackage('sqliteeventtable', @Register);
end.
