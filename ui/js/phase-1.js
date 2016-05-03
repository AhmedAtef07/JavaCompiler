$(function() {
    var fs = require('fs');

    var JavaCompilerPath = "../";
    var sys = require('sys');
    var exec = require('child_process').execFile;
    var child;

    $('#run-phase-1').click(function() {
        var command = JavaCompilerPath + 'bin/main';
        var args = [
            JavaCompilerPath + 'lexical/lexical_input.txt'
        ];

        fs.writeFileSync( JavaCompilerPath + "lexical/lexical_input.txt", ace.edit('lexical-editor').getValue());
        fs.writeFileSync( JavaCompilerPath + "bin/input.java", ace.edit('input-code-editor').getValue());

        child = exec(command, args, function(err, stdout, stderr) {
            if (err) { console.error('Error: ' + err); }
            if (stderr) { console.error('STDERR' + stderr); }

            console.info(stdout);
            var output = stdout.split('\n');
            var lexemesDetailed = $.trim(output[1].split(":")[1]);
            
            $('#output .nav').append('<li role="presentation" class="active"><a href="#lexemes-detailed" aria-controls="lexemes-detailed" role="tab" data-toggle="tab">Lexemes Detailed Output</a></li>');
            $('#output .tab-content').append('<div role="tabpanel" class="tab-pane active" id="lexemes-detailed"> <div id="lexemes-detailed-editor" class="editor" style="height:600px;margin-bottom:5px"></div> </div>');
            $('#lexemes-detailed-editor').text(fs.readFileSync(lexemesDetailed));

            var lexemesDetailedEditor = ace.edit("lexemes-detailed-editor");
            lexemesDetailedEditor.setTheme("ace/theme/monokai");
            var lexemesDetailedEditorSession = lexemesDetailedEditor.getSession();
            lexemesDetailedEditorSession.setUseWrapMode(true);
            lexemesDetailedEditorSession.setWrapLimit(100);
        });
        
    });




});