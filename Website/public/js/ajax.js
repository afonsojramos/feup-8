function ajaxCallPost(url, params, handler)
{
    let token = document.querySelector("#csrfToken").content;
    params._token = token;
    $.ajax(
    {
        url: url,
        type: 'POST',
        data: params,
        success: handler
    });
}

function getQueryVariable(variable, query)
{
    var vars = query.split("&");
    for (var i=0;i<vars.length;i++) {
           var pair = vars[i].split("=");
           if(pair[0] == variable){return pair[1];}
    }
    return(false);
}

if (window.location.pathname === "/exercise")
{
    let forms = document.querySelectorAll(".form-hint");
    for (let i = 0; i < forms.length; i++)
    {
        let form = forms[i];

        form.addEventListener("submit", function(event)
        {
            event.preventDefault();
            let params = new URLSearchParams(new FormData(form)).toString();
            let id = getQueryVariable("testID", params);
            let url = '/api/test/' + id + '/tip';
            ajaxCallPost(url, params, function()
            {
                console.log("Success");
            });
        });
    }
}
