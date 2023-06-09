Imports System
Imports EnvDTE
Imports EnvDTE80
Imports EnvDTE90
Imports System.IO
Imports System.Diagnostics

' A collection of helper methods to make using perforce with visual studio easy,
' without using the junky SCC plugin
'
' They assume:
'   1) Your credentials are cached (e.g., P4 token authentication)
'   2) P4.exe is in the visual studio executables path (add it if they don't work)
'
' I haven't tested them with multiple depots or clientspecs on one machine, you might need to
' make some additional changes if this is the case.  However, I suspect multiple clientspecs aren't
' a issue as long as you've got the one containing the files you're trying to edit active.
'
' See Source\suggested_perforce_menu_layout.png for how I've got the commands setup in my IDE
'
Public Module Perforce
    ' This path is the diffing program to use (Beyond Compare 2 on a Win64 machine; edit for BC3 or Araxis or x86 machine)
    Dim DiffingProgramPath As String = """c:\Program Files (x86)\Beyond Compare 2\BC2.exe"""

    ' This path is the P4 executable to use (shouldn't need to be modified unless it's not in the path)
    Dim P4Path As String = """P4.exe"""

    ' The output window to use must contain this string
    Dim TargetOutputWindowContains As String = "Build"


    ' Adds the active file to the depot
    Sub P4Add()
        If DTE.ActiveWindow.Document Is Nothing Then
            MsgBox("No document is selected.  Please click on a editor tab first.", MsgBoxStyle.OkOnly)
            WriteToOutputPane("No document was selected.")
            Return
        End If

        Dim filename As String = DTE.ActiveWindow.Document.FullName
        ExecuteCommand(P4Path, "add """ + filename + """")
    End Sub
    ' Checks out the active file
    Sub P4Edit()
        If DTE.ActiveWindow.Document Is Nothing Then
            MsgBox("No document is selected.  Please click on a editor tab first.", MsgBoxStyle.OkOnly)
            WriteToOutputPane("No document was selected.")
            Return
        End If

        Dim filename As String = DTE.ActiveWindow.Document.FullName
        ExecuteCommand(P4Path, "edit """ + filename + """")
    End Sub
    ' Outputs the difference between the active file and it's previous checked in version using the default diffing tool
    ' Warning: Saves the active file
    Sub P4Diff()
        If DTE.ActiveWindow.Document Is Nothing Then
            MsgBox("No document is selected.  Please click on a editor tab first.", MsgBoxStyle.OkOnly)
            WriteToOutputPane("No document was selected.")
            Return
        End If

        Dim doc As EnvDTE.Document = DTE.ActiveWindow.Document
        Dim filename As String = doc.FullName
        Dim info As FileInfo = New FileInfo(filename)

        If Not doc.Saved And Not info.IsReadOnly Then
            doc.Save()
        End If

        ExecuteCommand(P4Path, "diff """ + filename + """")
    End Sub
    ' Pops up the difference between the active file and it's previous checked in version using the diffing program of choice
    ' Warning: Saves the active file
    Sub P4DiffUsingApp()
        If DTE.ActiveWindow.Document Is Nothing Then
            MsgBox("No document is selected.  Please click on a editor tab first.", MsgBoxStyle.OkOnly)
            WriteToOutputPane("No document was selected.")
            Return
        End If

        Dim doc As EnvDTE.Document = DTE.ActiveWindow.Document
        Dim filename As String = doc.FullName
        Dim info As FileInfo = New FileInfo(filename)

        If Not doc.Saved And Not info.IsReadOnly Then
            doc.Save()
        End If

        ' Get the head copy
        Dim TempFileName = Path.GetTempFileName()
        ExecuteCommandNoOutput(P4Path, "print -o """ + TempFileName + """ """ + filename + """")

        ' Invoke the diff tool
        ExecuteCommandNoWaiting(DiffingProgramPath, """" + TempFileName + """ """ + filename + """")
    End Sub
    ' Reverts the active file
    Sub P4Revert()
        If DTE.ActiveWindow.Document Is Nothing Then
            MsgBox("No document is selected.  Please click on a editor tab first.", MsgBoxStyle.OkOnly)
            WriteToOutputPane("No document was selected.")
            Return
        End If

        Dim filename As String = DTE.ActiveWindow.Document.FullName
        ExecuteCommand(P4Path, "revert " + filename)
    End Sub
    ' Pops up a dialog box to confirm before reverting any changes in the active file
    Sub P4SafeRevert()
        If DTE.ActiveWindow.Document Is Nothing Then
            MsgBox("No document is selected.  Please click on a editor tab first.", MsgBoxStyle.OkOnly)
            WriteToOutputPane("No document was selected.")
            Return
        End If

        Dim filename As String = DTE.ActiveWindow.Document.FullName
        If MsgBox("Are you sure you want to revert the changes in '" + filename + "'?", MsgBoxStyle.YesNo Or MsgBoxStyle.Question Or MsgBoxStyle.DefaultButton2) = MsgBoxResult.Yes Then
            DTE.ActiveWindow.Document.Save()
            ExecuteCommand(P4Path, "revert """ + filename + """")
        End If
    End Sub
    ' Shows the revision history for the active file
    Sub P4History()
        If DTE.ActiveWindow.Document Is Nothing Then
            MsgBox("No document is selected.  Please click on a editor tab first.", MsgBoxStyle.OkOnly)
            WriteToOutputPane("No document was selected.")
            Return
        End If

        Dim filename As String = DTE.ActiveDocument.FullName
        ExecuteCommand(P4Path, "filelog -t -l -s """ + filename + """")
    End Sub
    ' Checks out any files that are currently modified but marked as read-only in the editor
    Sub P4EditAllModifiedDocuments()
        ' Prepare the status bar
        Dim status As EnvDTE.StatusBar = DTE.StatusBar
        Dim index As Integer = 0
        Dim count As Integer = DTE.Documents.Count

        ' Iterate over all open documents
        For Each document As EnvDTE.Document In DTE.Documents
            Dim info As FileInfo = New FileInfo(document.FullName)

            ' Only attempt to check out the file, if it is read only and was modified
            If Not document.Saved And info.IsReadOnly Then
                WriteToOutputPane("Checking out document", document.FullName)
                ExecuteCommand(P4Path, "edit """ + document.FullName + """")
            End If

            ' Update the status bar with the file name
            status.Progress(True, document.FullName, index, count)
            index += 1
        Next document
        status.Progress(False)
    End Sub
    ' Checks out any files that are currently modified but marked as read-only in the editor; and then saves them
    Sub P4EditAndSaveAllModifiedDocuments()
        ' Prepare the status bar
        Dim status As EnvDTE.StatusBar = DTE.StatusBar
        Dim index As Integer = 0
        Dim count As Integer = DTE.Documents.Count

        ' Iterate over all open documents
        For Each document As EnvDTE.Document In DTE.Documents
            Dim info As FileInfo = New FileInfo(document.FullName)

            ' Only attempt to check out the file, if it is read only and was modified
            If Not document.Saved And info.IsReadOnly Then
                WriteToOutputPane("Checking out and saving document", document.FullName)
                ExecuteCommand(P4Path, "edit """ + FileName + """")
                document.Save()
            End If

            ' Update the status bar with the file name
            status.Progress(True, document.FullName, index, count)
            index += 1
        Next document

        status.Progress(False)
    End Sub
    ' Executes a command, grabbing the output and sticking it in a output pane
    Public Sub ExecuteCommand(ByVal filename As String, ByVal arguments As String)
        Dim p As New System.Diagnostics.Process
        p.StartInfo.UseShellExecute = False
        p.StartInfo.FileName = filename
        p.StartInfo.Arguments = arguments
        p.StartInfo.RedirectStandardOutput = True
        p.StartInfo.RedirectStandardError = True
        p.Start()

        WriteToOutputPane(filename + " " + arguments, p.StandardOutput.ReadToEnd + p.StandardError.ReadToEnd)

        p.WaitForExit()
    End Sub
    ' Executes a command
    Public Sub ExecuteCommandNoOutput(ByVal filename As String, ByVal arguments As String)
        Dim p As New System.Diagnostics.Process
        p.StartInfo.UseShellExecute = False
        p.StartInfo.FileName = filename
        p.StartInfo.Arguments = arguments
        p.Start()

        WriteToOutputPane(filename + " " + arguments)

        p.WaitForExit()
    End Sub
    ' Fire-and-forget command execution (e.g., launch an external windows GUI tool)
    Public Sub ExecuteCommandNoWaiting(ByVal filename As String, ByVal arguments As String)
        Dim p As New System.Diagnostics.Process
        p.StartInfo.UseShellExecute = False
        p.StartInfo.FileName = filename
        p.StartInfo.Arguments = arguments
        p.StartInfo.WindowStyle = ProcessWindowStyle.Maximized
        p.Start()
        WriteToOutputPane(filename + " " + arguments)
    End Sub
    ' Writes some text to the build output pane
    Public Sub WriteToOutputPane(ByVal text As String)
        Dim win As Window = DTE.Windows.Item(EnvDTE.Constants.vsWindowKindOutput)
        Dim ow As OutputWindow = win.Object

        For Each pane As OutputWindowPane In ow.OutputWindowPanes
            If (pane.Name.Contains(TargetOutputWindowContains)) Then
                pane.OutputString(text & vbCrLf)
                pane.Activate()
                Return
            End If
        Next pane
    End Sub
    ' Writes some text to the build output pane
    Public Sub WriteToOutputPane(ByVal command As String, ByVal results As String)
        WriteToOutputPane(command & vbCrLf & results)
    End Sub

End Module
