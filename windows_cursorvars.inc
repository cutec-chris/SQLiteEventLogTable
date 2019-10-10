  FSWbemLocator : OLEVariant;
  FWMIService   : OLEVariant;
  FWbemObjectSet: OLEVariant;
  {$IF FPC_FULLVERSION>20604}
  FWbemObject   : OLEVariant;
  {$ELSE}
  FWbemObject   : Variant;
  {$ENDIF}
  oEnum         : IEnumvariant;
  iValue        : LongWord;

