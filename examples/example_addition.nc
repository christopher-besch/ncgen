// x + y Calculator

// Setting type to HTML for JS (use [htmlindex] to generate index.html)
[html]

// Adding a title via JS-HTML for browser display
html.addtag <h2>Check the browser console.</h2>

// Input
printtext First number :
float x = 15
printvar x
printtext Second number :
float y = 5
printvar y
printtext Nr 1 + Nr 2 :
printvar x + y


// Is the result larger than 100 ?
if x + y > 100
<indent>
printtext The output larger than 100.
else
<indent>
printtext The output is not larger than 100.
endif

// Examples of language-specific functions
js.alerttext HEY ! THIS IS AN ALERT THAT WANTS YOUR ATTENTION !
py.sleep 2