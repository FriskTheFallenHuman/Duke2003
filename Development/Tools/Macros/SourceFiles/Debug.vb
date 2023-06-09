Imports System
Imports EnvDTE
Imports EnvDTE80
Imports EnvDTE90
Imports System.Diagnostics

Public Module Debug
    'Typically bound to "Ctrl-F4"
    Sub AttachToStartupProjectExecutable()
        Try
            Dim dbg2 As EnvDTE90.Debugger3 = DTE.Debugger
            Dim trans As EnvDTE80.Transport = dbg2.Transports.Item("Default")
            ' In order to enable managed code, change dbgeng(1) to dbgeng(2) and uncomment the "managed" line below
            Dim dbgeng(1) As EnvDTE80.Engine
            dbgeng(0) = trans.Engines.Item("Native")
            'dbgeng(1) = trans.Engines.Item("Managed")

            Dim sb As SolutionBuild = DTE.Solution.SolutionBuild
            Dim projName As String = sb.StartupProjects(0)

            'should be something like Windows\XXXGame Win32
            Dim IndexOfStartChar
            Dim IndexOfEndChar
            IndexOfStartChar = projName.IndexOf("\")
            IndexOfEndChar = projName.IndexOf(" ")

            Dim projNameToSearchFor = projName
            If ((IndexOfStartChar >= 0) And (IndexOfEndChar >= 0)) Then
                'advance to the one AFTER the '\'
                IndexOfStartChar = IndexOfStartChar + 1
                projNameToSearchFor = projNameToSearchFor.Substring(IndexOfStartChar, IndexOfEndChar - IndexOfStartChar)
            End If

            Dim processes As EnvDTE.Processes = DTE.Debugger.LocalProcesses
            For Each proc As EnvDTE80.Process2 In processes
                If proc.Name.Contains(projNameToSearchFor) Then
                    proc.Attach2(dbgeng)
                    Return
                End If
            Next
        Catch ex As System.Exception
            MsgBox(ex.Message)
        End Try
    End Sub
End Module



