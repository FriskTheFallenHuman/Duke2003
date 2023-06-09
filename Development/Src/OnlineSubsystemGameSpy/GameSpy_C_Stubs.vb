Imports System
Imports EnvDTE
Imports EnvDTE80
Imports System.Diagnostics

Public Module GameSpy_C_Stubs


    Sub GenerateGameSpyCStubs()
        Dim project As Project
        Dim projectObjects As Object()
        Dim window As Window
        Dim target As Object
        Dim GameSpyProject As ProjectItem
        Dim TargetProject As ProjectItem

        window = DTE.Windows.Item(Constants.vsWindowKindCommandWindow)
        projectObjects = DTE.ActiveSolutionProjects
        If projectObjects.Length = 0 Then
            Exit Sub
        End If
        project = DTE.ActiveSolutionProjects(0)
        If (DTE.ActiveWindow Is window) Then
            target = window.Object
        Else
            target = GetOutputWindowPane("Generating GameSpy C Stubs")
            target.Clear()
        End If
        target.OutputString("Find GameSpy")
        target.OutputString(Microsoft.VisualBasic.Constants.vbCrLf)
        GameSpyProject = FindProjectItem(project, "GameSpy")
        target.OutputString("Find Target")
        target.OutputString(Microsoft.VisualBasic.Constants.vbCrLf)
        TargetProject = FindProjectItem(project, "GameSpy_C_Stubs")
        If Not (GameSpyProject Is Nothing) Then
            target.OutputString("recurse")
            target.OutputString(Microsoft.VisualBasic.Constants.vbCrLf)
            '' Iterate the project recursively adding stub C files for each member
            RecursivelyAddCStubs(GameSpyProject, TargetProject, target)
        End If
    End Sub

    Function GetOutputWindowPane(ByVal Name As String, Optional ByVal show As Boolean = True) As OutputWindowPane
        Dim window As Window
        Dim outputWindow As OutputWindow
        Dim outputWindowPane As OutputWindowPane

        window = DTE.Windows.Item(EnvDTE.Constants.vsWindowKindOutput)
        If show Then window.Visible = True
        outputWindow = window.Object
        Try
            outputWindowPane = outputWindow.OutputWindowPanes.Item(Name)
        Catch e As System.Exception
            outputWindowPane = outputWindow.OutputWindowPanes.Add(Name)
        End Try
        outputWindowPane.Activate()
        Return outputWindowPane
    End Function

    Function FindProjectItem(ByVal StartProject As EnvDTE.Project, ByVal SearchName As String)
        Dim projectItem As EnvDTE.ProjectItem
        Dim FoundProject As EnvDTE.ProjectItem

        For Each projectItem In StartProject.ProjectItems
            Dim projectItems2 As EnvDTE.ProjectItems
            Dim notSubCollection As Boolean

            If projectItem.FileNames(0) = SearchName Then
                Return projectItem
            Else
                FoundProject = FindProjectInProjectItem(projectItem, SearchName)
                If Not (FoundProject Is Nothing) Then
                    Return FoundProject
                End If
            End If
        Next
        Return Nothing
    End Function
    Function FindProjectInProjectItem(ByVal StartProject As EnvDTE.ProjectItem, ByVal SearchName As String) As ProjectItem
        Dim projectItem As EnvDTE.ProjectItem
        Dim FoundProject As EnvDTE.ProjectItem

        For Each projectItem In StartProject.ProjectItems
            Dim projectItems2 As EnvDTE.ProjectItems
            Dim notSubCollection As Boolean

            If projectItem.FileNames(0) = SearchName Then
                Return projectItem
            Else
                FoundProject = FindProjectInProjectItem(projectItem, SearchName)
                If Not (FoundProject Is Nothing) Then
                    Return FoundProject
                End If
            End If
        Next
        Return Nothing
    End Function

    Function RecursivelyAddCStubs(ByVal SourceProj As EnvDTE.ProjectItem, ByVal TargetProj As EnvDTE.ProjectItem, ByVal outputWinPane As Object)
        Dim ProjectItem As EnvDTE.ProjectItem
        Dim FileName As String
        Dim CreatedFileName As String

        ''        EmptyTarget(TargetProj)

        '' For each project item that is a file, create a corresponding stub file
        For Each ProjectItem In SourceProj.ProjectItems
            FileName = ProjectItem.FileNames(1)
            If FileName.EndsWith(".c") Then
                '' Creates the stub file if not already present
                CreatedFileName = CreateStubFile(FileName)
                If CreatedFileName.Length > 0 Then
                    '' Add to the target project
                    AddToProject(TargetProj, CreatedFileName, outputWinPane)
                End If
            End If
            '' Now check the next item's children
            RecursivelyAddCStubs(ProjectItem, TargetProj, outputWinPane)
        Next
    End Function

    Function EmptyTarget(ByVal TargetProj As EnvDTE.ProjectItem)
        Dim projectItem As EnvDTE.ProjectItem

        For Each projectItem In TargetProj.ProjectItems
            projectItem.Remove()
        Next
    End Function

    Function AddToProject(ByVal TargetProj As EnvDTE.ProjectItem, ByVal CreatedFileName As String, ByVal outputWinPane As Object)
        outputWinPane.OutputString(CreatedFileName)
        outputWinPane.OutputString(Microsoft.VisualBasic.Constants.vbCrLf)
        ''todo auto add to project
    End Function

    Function CreateStubFile(ByVal SourceFileName As String) As String
        Dim CreatedFileName As String
        Dim OutputPath As String
        Dim GSDir As String
        Dim Index As Integer
        Dim EndIndex As Integer
        Dim OutFile As System.IO.StreamWriter


        '' Snip off the file name
        Index = SourceFileName.LastIndexOf("\")
        CreatedFileName = SourceFileName.Substring(Index + 1)
        '' Figure out the path that we want to write to
        Index = SourceFileName.LastIndexOf("Development\")
        OutputPath = SourceFileName.Substring(0, Index + "Development\".Length)
        OutputPath = OutputPath + "Src\OnlineSubsystemGameSpy\GameSpy_C_Stubs\_stub_"
        '' Find the subdir used by gamespy for proper include
        Index = SourceFileName.LastIndexOf("GameSpy\")
        EndIndex = SourceFileName.LastIndexOf("\")
        GSDir = SourceFileName.Substring(Index, EndIndex - Index)
        GSDir = GSDir.Replace("\", "/")

        '' Create the file
        OutFile = My.Computer.FileSystem.OpenTextFileWriter(OutputPath + CreatedFileName, False)
        '' Write the C source to the file
        OutFile.WriteLine("")
        OutFile.WriteLine("/** Autogenerated file. Do not edit */")
        OutFile.WriteLine("")
        OutFile.WriteLine("#if !PS3")
        OutFile.WriteLine("     #pragma warning(disable : 4206)")
        OutFile.WriteLine("#endif")
        OutFile.WriteLine("")
        OutFile.WriteLine("#include ""UnBuild.h""")
        OutFile.WriteLine("")
        OutFile.WriteLine("#if WITH_GAMESPY")
        OutFile.WriteLine("     #include ""../../External/" + GSDir + "/" + CreatedFileName + """")
        OutFile.WriteLine("#endif")
        OutFile.WriteLine("")
        OutFile.WriteLine("")
        '' Clean up the file...
        OutFile.Close()

        Return OutputPath + CreatedFileName

    End Function
End Module
