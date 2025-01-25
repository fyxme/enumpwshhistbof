# enumpwshhist BOF

`enumpwshhist` is a Beacon Object File (BOF) that enumerates and finds sensitive information in PowerShell history files. This attempts to access the PowerShell history file directory of all users and will grep lines for a number of pre-defined keywords.

The behaviour is the same as the [Powershell History netexec SMB Module](https://github.com/Pennyw0rth/NetExec/blob/main/nxc/modules/powershell_history.py) except you can now run it from your favorite C2 or BOF runner.

> **enumpwshhist:** **enum**ERATE **p**O**w**ER**sh**ELL **hist**ORY

## Usage

```
enumpwshhist
```

### Example output

```
22/01/2025 15:56:46 [danielward] Demon » enumpwshhist
[*] [5E924F7B] Enumerating powershell history for all reachable directories
[+] Send Task to Agent [31 bytes]
[+] Received Output [42 bytes]:
[+] Enumerating powershell history files!

[+] Received Output [736 bytes]:
Evaluating directory: C:\Users\lo\AppData\Roaming\Microsoft\Windows\PowerShell\PSReadLine
	File found: ConsoleHost_history.txt
	Full path: C:\Users\lo\AppData\Roaming\Microsoft\Windows\PowerShell\PSReadLine\ConsoleHost_history.txt
	Sensitive keywords found:
		[convertto-securestring] $creds = convertto-securestring 'helloworld123' -asplaintext -force
		[credential] $uo = new-object system.manageement.automation.pscredential ('micael.jackson', $creds)
		[credential] $uo = new-object system.manageement.automation.pscredential ('michael.jackson', $creds)
		[credential] $uo = new-object system.management.automation.pscredential ('michael.jackson', $creds)
		[convertto-securestring] $creds = convertto-securestring 'h123elloworld123' -asplaintext -force

[+] Received Output [42 bytes]:
[+] Finished powershell file enumeration!

[*] BOF execution completed
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

- [netexec's powershell history module](https://github.com/Pennyw0rth/NetExec/blob/main/nxc/modules/powershell_history.py), which this BOF is based on
- wsummerhill's [enumfiles](https://github.com/wsummerhill/BOF-enumfiles) BOF which has a powershell history module which lists powershell history files. However, only works for the current user only and requires the `APPDATA` environment variable to be set which is not always the case.
