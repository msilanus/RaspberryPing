<!DOCTYPE html>
<HTML>
<HEAD>

<style>
body {
	background-color : black;
	color : white;
	font-family : Arial, Helvetica, sans-serif;
}
div {
	font-size : 75%;
}
</style>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
   	<TITLE>Mon objet connect&eacute;</TITLE>
	
</HEAD>

<BODY>
<center><h1>Mesure de distance</h1>
	<p>
	<p>
	<p>
		<h2><?php
		   $lines    = file("distance.log");
		   foreach($lines as $line)
		   {
		      echo($line);
	 	   }
		   //$lastLine = array_pop($lines);
		   //list($horodate, $distance) = split("   |   ",$lastline);
		   //echo $lastline;
		
		?></h2>
</center>



</body>
</html>

