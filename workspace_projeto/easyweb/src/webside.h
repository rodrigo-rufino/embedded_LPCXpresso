/******************************************************************
 *****                                                        *****
 *****  Name: webside.c                                       *****
 *****  Ver.: 1.0                                             *****
 *****  Date: 07/05/2001                                      *****
 *****  Auth: Andreas Dannenberg                              *****
 *****        HTWK Leipzig                                    *****
 *****        university of applied sciences                  *****
 *****        Germany                                         *****
 *****        adannenb@et.htwk-leipzig.de                     *****
 *****  Func: example HTML-code for easyweb.c                 *****
 *****                                                        *****
 ******************************************************************/

const unsigned char WebSide[] = {
"<html>"
"<head>"
"<title>EC020</title>"
"<style type=\"text/css\">"
"body{font-family: \"Verdana\", \"Geneva\", sans-serif;width: 400px;margin: 0 auto;}"
"</style>"
"</head>"
""
"<body>"
"<p><b><font color=\"#FFFFFF\" size=\"6\"><i>Projeto de Topicos Avancados!</i></font></b></p>"
"<h1>Temperatura</h1>"
"<p>\"AD1%\" graus</p>"

"<h1>Acelerometro</h1>"
"<p>x = \"AD2%\"</p>"
"<p>y = \"AD3%\"</p>"
"<p>z = \"AD4%\"</p>"

""
"<h1>Nivel</h1>"
""
"<table bgcolor=\"#ff0000\" border=\"1\" cellpadding=\"0\" cellspacing=\"0\" width=\"200\">"
"<tr>"
"<td>"
"<table width=\"AD5%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\">"
"<tr><td bgcolor=\"#00ff00\">&nbsp;</td></tr>"
"</table>"
"</td>"
"</tr>"
"</table>"
""
"<table border=\"0\" width=\"200\">"
"<tr>"
"<td width=\"20%\">0</td>"
"<td width=\"20%\"> </td>"
"<td width=\"20%\"> </td>"
"<td width=\"20%\"> </td>"
"<td width=\"20%\">10</td>"
"</tr>"
"</table>"
"</body>"
"</html>"};