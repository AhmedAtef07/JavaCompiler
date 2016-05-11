$(function() {
    var fs = require('fs');
    
    $('#lexical-editor').text(fs.readFileSync("../lexical/lexical_input.txt"));
    $('#grammer-editor').text(fs.readFileSync("../syntax/CFG.txt"));
    // $('#input-code-editor').text(fs.readFileSync("../bin/input.java"));

    var lexicalEditor = ace.edit("lexical-editor");
    lexicalEditor.setTheme("ace/theme/monokai");
    var lexicalEditorSession = lexicalEditor.getSession();
    lexicalEditorSession.setUseWrapMode(true);
    lexicalEditorSession.setWrapLimit(100);


    var grammerEditor = ace.edit("grammer-editor");
    grammerEditor.setTheme("ace/theme/monokai");
    var grammerEditorSession = grammerEditor.getSession();
    grammerEditorSession.setUseWrapMode(true);
    grammerEditorSession.setWrapLimit(100);

    var inputCodeEditor = ace.edit("input-code-editor");
    inputCodeEditor.setTheme("ace/theme/monokai");
    var inputCodeEditorSession = inputCodeEditor.getSession();
    inputCodeEditorSession.setUseWrapMode(true);
    inputCodeEditorSession.setWrapLimit(100);
    inputCodeEditorSession.setMode("ace/mode/java");

});
