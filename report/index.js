


$(function() {
    localStorage.clear();

    for(var key in dfas) {
        dfas[$.trim(key).toLowerCase()] = dfas[key];
    }
    delete dfas[" break"];

   var dfa_values = Object.keys(dfas);
   dfa_values.sort();
   

   // console.info(dfa_names);
   for (var i = 0; i < dfa_values.length; i++) {
        // var option = $('option').attr('value', dfa_names[i]).text($.trim(dfa_names[i]));
        // console.info(option);
        var t = $.trim(dfa_values[i]);
        $('#dfas').append($("<option></option>")
                    .attr("value", dfa_values[i])
                    .text(t.split('_')[0]));

    }

    $('.selectpicker').selectpicker({
      style: 'btn-primary',
      size: 20
    });

    $('#dfas').change(function(event) {
        localStorage.clear();
        window.nodes = [];
        window.links = [];
        window.reDraw();
        // $('#canvas').remove();
        // delete canvas
        localStorage.fsm = JSON.stringify(dfas[$(this).val()]);
        window.reDraw();
    });
});

