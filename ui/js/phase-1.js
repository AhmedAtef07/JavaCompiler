/*jshint esnext: true */

$(function() {
    var fs = require('fs');

    var JavaCompilerPath = "../";
    var sys = require('sys');
    var exec = require('child_process').execFile;
    var child;

    var goToByScroll = function (selector){
          // Remove "link" from the ID
        $('html,body').animate({
            scrollTop: selector.offset().top},
            'slow');
    };

    $('#run-phase-1').click(function() {
        var command = JavaCompilerPath + 'bin/ui';
        var args = [
            JavaCompilerPath + 'lexical/lexical_input.txt',
            JavaCompilerPath + 'syntax/CFG.txt'
        ];

        fs.writeFileSync( JavaCompilerPath + "lexical/lexical_input.txt", ace.edit('lexical-editor').getValue());
        fs.writeFileSync( JavaCompilerPath + "bin/input.java", ace.edit('input-code-editor').getValue());

        child = exec(command, args, function(err, stdout, stderr) {
            if (err) { console.error('Error: ' + err); }
            if (stderr) { console.error('STDERR' + stderr); }

            console.info(stdout);
            var output = stdout.split('\n');
            var lexemes = $.trim(output[0].split(":")[1]);
            var lexemesDetailed = $.trim(output[1].split(":")[1]);
            var first = $.trim(output[3].split(':')[1]);
            var follow = $.trim(output[4].split(':')[1]);
            var parsingTable = $.trim(output[5].split(':')[1]);

            if(!stderr && !err) goToByScroll($('#output'));
            
            $('#output .nav').append('<li role="presentation"><a href="#lexemes" aria-controls="lexemes" role="tab" data-toggle="tab">Lexemes</a></li>');
            $('#output .tab-content').append('<div role="tabpanel" class="tab-pane" id="lexemes"> <div id="lexemes-editor" class="editor" style="height:700px;margin-bottom:5px"></div> </div>');

            $('#output .nav').append('<li role="presentation" class="active"><a href="#lexemes-detailed" aria-controls="lexemes-detailed" role="tab" data-toggle="tab">Lexemes Detailed Output</a></li>');
            $('#output .tab-content').append('<div role="tabpanel" class="tab-pane active" id="lexemes-detailed"> <div id="lexemes-detailed-editor" class="editor" style="height:700px;margin-bottom:5px"></div> </div>');

            $('#output .nav').append('<li role="presentation"><a href="#first" aria-controls="first" role="tab" data-toggle="tab">First</a></li>');
            $('#output .tab-content').append('<div role="tabpanel" class="tab-pane" id="first"> ' + fs.readFileSync(first) + ' </div>');

            $('#output .nav').append('<li role="presentation"><a href="#follow" aria-controls="follow" role="tab" data-toggle="tab">Follow</a></li>');
            $('#output .tab-content').append('<div role="tabpanel" class="tab-pane" id="follow"> ' + fs.readFileSync(follow) + ' </div>');

            $('#output .nav').append('<li role="presentation"><a href="#parsingTable" aria-controls="parsingTable" role="tab" data-toggle="tab">Parsing Table</a></li>');
            $('#output .tab-content').append('<div role="tabpanel" class="tab-pane" id="parsingTable"> <div class="table-responsive">' + fs.readFileSync(parsingTable) + '</div></div>');
            $('#output').html( $('#output').html().replace(new RegExp('\\\\L', 'g'), '&epsilon;') );

            // $('#output .nav').append('<li role="presentation"><a href="#stack-output" aria-controls="lexemes-detailed" role="tab" data-toggle="tab">Stack Output</a></li>');
            // $('#output .tab-content').append(
            //     `<div role="tabpanel" class="tab-pane active" id="stack-output">
            //         <div class="panel-group" id="accordion" role="tablist" aria-multiselectable="true">
            //           <div class="panel panel-default">
            //             <div class="panel-heading" role="tab" id="headingOne">
            //               <h4 class="panel-title">
            //                 <a role="button" data-toggle="collapse" data-parent="#accordion" href="#token-1" aria-expanded="false" aria-controls="token-1">
            //                   Collapsible Group Item #1
            //                 </a>
            //               </h4>
            //             </div>
            //             <div id="token-1" class="panel-collapse collapse in" role="tabpanel" aria-labelledby="headingOne">
            //               <div class="panel-body">first token</div>
            //             </div>
            //           </div>
            //         </div>
            //     </div>`
            // );
            

            $('#lexemes-detailed-editor').text(fs.readFileSync(lexemesDetailed));
            var lexemesDetailedEditor = ace.edit("lexemes-detailed-editor");
            lexemesDetailedEditor.setTheme("ace/theme/monokai");
            var lexemesDetailedEditorSession = lexemesDetailedEditor.getSession();
            lexemesDetailedEditorSession.setUseWrapMode(true);
            lexemesDetailedEditorSession.setWrapLimit(100);

            $('#lexemes-editor').text(fs.readFileSync(lexemes));
            var lexemesEditor = ace.edit("lexemes-editor");
            lexemesEditor.setTheme("ace/theme/monokai");
            var lexemesEditorSession = lexemesEditor.getSession();
            lexemesEditorSession.setUseWrapMode(true);
            lexemesEditorSession.setWrapLimit(100);
        });
        
    });




});