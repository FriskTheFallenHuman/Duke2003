Imports System
Imports EnvDTE
Imports EnvDTE80
Imports EnvDTE90
Imports System.Diagnostics

Public Module TextEditor
    'Typically bound to "Ctrl-Alt-F"
    Sub FindInSolution()
        DTE.ExecuteCommand("View.TrackActivityInSolutionExplorer")
        DTE.ExecuteCommand("View.TrackActivityInSolutionExplorer")
    End Sub

    ' Builds a helper-struct with constructor from the highlighted variable declarations
    Sub MakeStruct()
        Dim TS As TextSelection = DTE.ActiveDocument.Selection
        Dim SelectionLines() As String = TS.Text.Split(vbNewLine)

        Dim ConstructorDecl As String
        Dim ConstructorInit As String

        Dim StructName As String = InputBox("Enter a name for the struct")
        If StructName <> "" Then
            TS.Delete()
            TS.Indent()
            TS.Insert("struct " + StructName)
            TS.NewLine()
            TS.Unindent()
            TS.Insert("{")
            TS.NewLine()

            For Each Line In SelectionLines
                Line = Line.Trim()
                Dim i = Line.IndexOf(";")
                If i <> -1 Then
                    Dim ExprText As String = Line.Substring(0, i)

                    If ExprText <> "" Then
                        i = ExprText.LastIndexOf(" ")
                        Dim VarType As String = ExprText.Substring(0, i)
                        Dim VarName As String = ExprText.Substring(i + 1)

                        If ConstructorDecl <> "" Then
                            ConstructorDecl = ConstructorDecl + ", "
                        End If
                        ConstructorDecl = ConstructorDecl + VarType + " In" + VarName

                        If ConstructorInit <> "" Then
                            ConstructorInit = ConstructorInit + "," + vbTab + VarName + "(In" + VarName + ")" + vbNewLine
                        Else
                            ConstructorInit = ConstructorInit + ":" + vbTab + VarName + "(In" + VarName + ")" + vbNewLine
                        End If
                    End If
                End If

                TS.Insert(Line)
                TS.NewLine()
            Next

            ConstructorInit = ConstructorInit + "{}"

            TS.Insert(StructName + "(" + ConstructorDecl + ")")
            TS.NewLine()
            TS.Unindent()
            For Each Line In ConstructorInit.Split(vbNewLine)
                TS.Insert(Line.Trim())
                TS.NewLine()
            Next
            TS.Unindent()
            TS.Insert("};")
            TS.NewLine()
        End If
    End Sub

End Module
