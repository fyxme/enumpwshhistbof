# enumpwshhist BOF

`enumpwshhist` is a Beacon Object File (BOF) that enumerates and finds sensitive information in PowerShell history files. This attempts to access the PowerShell history file directory of all users and will grep lines for a number of pre-defined keywords.

The behaviour is the same as the [Powershell History netexec SMB Module](https://github.com/Pennyw0rth/NetExec/blob/main/nxc/modules/powershell_history.py) except you can now run it from your favorite C2 or BOF runner.

> **enumpwshhist:** **enum**ERATE **p**O**w**ER**sh**ELL **hist**ORY

## Usage

```
enumpwshhist
```

## Supported C2s

- CobaltStrike : load `enumpwshhist.cna`
- Havoc : load `havoc-enumpwshhist.py`

## Compilation

The makefile is setup for cross platform compilation using mingw:

```
make
```

## Credits

wsummerhill's [enumfiles](https://github.com/wsummerhill/BOF-enumfiles) BOF which has a powershell history module which lists powershell history files. However, only works for the current user only and requires the `APPDATA` environment variable to be set which is not always the case.
