<?php

	function printLang($langlist)
	{
			echo "<div class=\"language\">\n";
			for ( $it = 0 ; $it < count( $langlist ) ; $it++ )
			{
				echo "<a class=\"lang\" href=\"./index.php?lang=".$langlist[$it]["lang"]."\" onMouseOver=\"javascript:$('#lang".$it."').show();\" onMouseOut=\"javascript:$('#lang".$it."').hide();\">\n";
				echo "<img src=\"./img/".$langlist[$it]["lang"].".png\" alt=\"en\" class=\"flag\">\n";
				echo "</a>\n";
				echo "<div class=\"viewercontainer langview\" id=\"lang".$it."\">\n";
				echo "<div class=\"viewer\">\n";
				echo "<p>".$langlist[$it]["text"]."</p>\n";
				echo "</div>\n";
				echo "</div>\n";
			}
			echo "</div>\n";
	}
	
	function getManualPage($it, $manualpagelist, $text)
	{
		$page = "<div id=\"manual".$it."\" class=\"textinside\">\n";
		$page .= "<a href=\"#\" onClick=\"javascript:$('#".$manualpagelist[($it-1)]["type"].$it."').show();\">\n";
		$page .= "<span class=\"zoom\">\n";
		$page .= "<span class=\"thumbcontainer\">\n";
		$page .= "<img src=\"./img/thumbnails/screenshot".$it.".jpeg\" class=\"allthumb ".$manualpagelist[($it-1)]["type"]."thumb\" alt=\"KFF screenshot\">\n";
		$page .= "</span>\n";
		$page .= "Click to enlarge&nbsp;\n";
		$page .= "<img src=\"./img/zoom.png\" class=\"zoom\" alt=\"Zoom\">\n";
		$page .= "</span>\n";
		$page .= "</a>\n";
		$page .= "<h4>".$manualpagelist[($it-1)]["title"]."</h4>\n";
		$page .= $text."\n";
		$page .= "<div class=\"viewercontainer ".$manualpagelist[($it-1)]["type"]."view\" id=\"".$manualpagelist[($it-1)]["type"].$it."\" onClick=\"javascript:$('#".$manualpagelist[($it-1)]["type"].$it."').hide();\">\n";
		$page .= "<div class=\"viewer\">\n";
		$page .= "<h1>".$manualpagelist[($it-1)]["title"]."</h1>\n";
		$page .= "<img src=\"./img/screenshot".$it.".jpeg\" class=\"".$manualpagelist[($it-1)]["type"]."view\" alt=\"KFF screenshot\">\n";
		$page .= "<p>Click on the window to close it</p>\n";
		$page .= "</div>\n";
		$page .= "</div>\n";
		$page .= "</div>\n";
		return $page;
	}
	
	function printTab( $it, $text, $manual = false )
	{
		echo "<div id=\"tab".$it."\" class=\"tabcontent\">\n";
		if ( !$manual )
		{
			echo "<div class=\"inside\">\n";
			echo "<div class=\"textinside\">\n";
		}
		echo $text."\n";
		if ( !$manual )
		{
			echo "</div>\n";
			echo "</div>\n";
		}
		echo "</div>\n";
	}
	
	function printMenu($titlelist)
	{
		echo "<div class=\"menu\">\n";
		for ( $it = 0 ; $it < count( $titlelist ) ; $it++ )
		{
			if ( $it == 1 )
			{
				$act = " activated";
			}
			else
			{
				$act = "";
			}
			echo "<a href=\"#\" class=\"tabmenu".$act."\" onClick=\"javascript:manualtab=".$it.";showTab(manualtab);\"";
			if ( count( $titlelist[$it]["sub"] ) )
			{
				echo " onMouseOver=\"javascript:$('#sub".$it."').show();\"";
			}
			echo ">".$titlelist[$it]["title"]."</a>\n";
			for ( $it2 = 0 ; $it2 < count( $titlelist[$it]["sub"] ) ; $it2++ )
			{
				if ( $it2 == 0)
				{
					echo "<div id=\"sub".$it."\" class=\"subtitle\" onMouseOut=\"javascript:$('#sub".$it."').hide();\">\n";
					echo "<ul>\n";
				}
				echo "<li><a href=\"#".$titlelist[$it]["sub"][$it2]["link"]."\">".$titlelist[$it]["sub"][$it2]["text"]."</a></li>\n";
				if ( $it2 == ( count( $titlelist[$it]["sub"] ) -1 ) )
				{
					echo "</ul>\n";
					echo "</div>\n";
				}
			}
		}
		echo "&nbsp;<img src=\"./img/logo.png\" class=\"logo\" >\n";
		echo "</div>\n";
		echo "<div class=\"menubottom\">\n";
		for ( $it = 0 ; $it < count( $titlelist ) ; $it++ )
		{
			echo "<span class=\"bottommenu bottommenuinactive\" id=\"menu".$it."\"></span>\n";
		}
		echo "</div>\n";
	}
	
	function printTicker( $tickerlist )
	{
		echo "<div class=\"ticker\">\n";
		echo "<ul id=\"ticker01\">\n";
		for ( $it = 0 ; $it < count( $tickerlist ) ; $it++ )
		{
			echo "<li>\n";
			echo "<img src=\"./img/plane.png\" alt=\"\" width=\"68\" height=\"18\">\n";
			echo "<span>".$tickerlist[$it]["date"]."\n";
			echo "</span>\n";
			echo "<a href=\"#\">".$tickerlist[$it]["text"]."</a>\n";
			echo "</li>\n";
		}
		echo "<!-- eccetera -->\n";
		echo "</ul>\n";
		echo "</div>\n";
	}
	
	function printHeader()
	{
		echo "<div class=\"header\">\n";
		echo "<span class=\"headerleft\"></span>\n";
		echo "<span class=\"headermiddle\"><img src=\"./img/logo.png\" class=\"logo\" >&nbsp;KFreeFlight</span>\n";
		echo "<span class=\"headerright\"></span>\n";
		echo "</div>\n";
	}
	
	$titlelist = array();
	$subtitlelist = array();
	$titlelist[0]["title"] = "Introduction";
	$subtitlelist = array();
	$subtitle["text"] = "What is it ?";
	$subtitle["link"] = "whatisit";
	array_push($subtitlelist, $subtitle);
	$subtitle["text"] = "Disclaimer";
	$subtitle["link"] = "disclaimer";
	array_push($subtitlelist, $subtitle);
	$subtitle["text"] = "License";
	$subtitle["link"] = "license";
	array_push($subtitlelist, $subtitle);
	$titlelist[0]["sub"] = $subtitlelist;
	$titlelist[1]["title"] = "News";
	$subtitlelist = array();
	$titlelist[1]["sub"] = $subtitlelist;
	$titlelist[2]["title"] = "Download";
	$subtitlelist = array();
	$subtitle["text"] = "Source tarball";
	$subtitle["link"] = "";
	array_push($subtitlelist, $subtitle);
	$subtitle["text"] = "Binary package";
	$subtitle["link"] = "";
	array_push($subtitlelist, $subtitle);
	$subtitle["text"] = "SVN";
	$subtitle["link"] = "";
	array_push($subtitlelist, $subtitle);
	$subtitle["text"] = "CVS";
	$subtitle["link"] = "";
	array_push($subtitlelist, $subtitle);
	$titlelist[2]["sub"] = $subtitlelist;
	$titlelist[3]["title"] = "FAQ";
	$subtitlelist = array();
	$titlelist[3]["sub"] = $subtitlelist;
	$titlelist[4]["title"] = "Mailing List";
	$subtitlelist = array();
	$titlelist[4]["sub"] = $subtitlelist;
	$titlelist[5]["title"] = "TODO";
	$subtitlelist = array();
	$titlelist[5]["sub"] = $subtitlelist;
	$titlelist[6]["title"] = "Manual";
	$subtitlelist = array();
	$titlelist[6]["sub"] = $subtitlelist;
	$titlelist[7]["title"] = "Thanks";
	$subtitlelist = array();
	$titlelist[7]["sub"] = $subtitlelist;
	
	$tickerlist = array();
	$tickerlist[0]["date"] = "01/01/2010";
	$tickerlist[0]["text"] = "A new SVN repository is available ( KDE4 version )";
	$tickerlist[1]["date"] = "01/01/2010";
	$tickerlist[1]["text"] = "CVS repository is out of date";
	$tickerlist[2]["date"] = "01/08/2010";
	$tickerlist[2]["text"] = "Last website update";
	
	$langlist = array();
	$langlist[0]["lang"] = "en";
	$langlist[0]["text"] = "English / American language";
	$langlist[1]["lang"] = "fr";
	$langlist[1]["text"] = "French language";
	$langlist[2]["lang"] = "it";
	$langlist[2]["text"] = "Italian language";
	$langlist[3]["lang"] = "de";
	$langlist[3]["text"] = "German language";
	
	$manualpagelist = array();
	$manualpagelist[0]["title"] = "Common Options";
	$manualpagelist[0]["type"] = "app";
	$manualpagelist[1]["title"] = "Rendering Options";
	$manualpagelist[1]["type"] = "app";
	$manualpagelist[2]["title"] = "Airport Options";
	$manualpagelist[2]["type"] = "app";
	$manualpagelist[3]["title"] = "Carrier Options";
	$manualpagelist[3]["type"] = "app";
	$manualpagelist[4]["title"] = "Aircraft Options";
	$manualpagelist[4]["type"] = "app";
	$manualpagelist[5]["title"] = "Start Position Options";
	$manualpagelist[5]["type"] = "app";
	$manualpagelist[6]["title"] = "Date Time Options";
	$manualpagelist[6]["type"] = "app";
	$manualpagelist[7]["title"] = "Weather Options";
	$manualpagelist[7]["type"] = "app";
	$manualpagelist[8]["title"] = "Flightplan Options";
	$manualpagelist[8]["type"] = "app";
	$manualpagelist[9]["title"] = "Network Options";
	$manualpagelist[9]["type"] = "app";
	$manualpagelist[10]["title"] = "NAV and COM Options";
	$manualpagelist[10]["type"] = "app";
	$manualpagelist[11]["title"] = "Scenario Options";
	$manualpagelist[11]["type"] = "app";
	$manualpagelist[12]["title"] = "Property Options";
	$manualpagelist[12]["type"] = "app";
	$manualpagelist[13]["title"] = "Personnal Options";
	$manualpagelist[13]["type"] = "app";
	$manualpagelist[14]["title"] = "Airport Search Tools";
	$manualpagelist[14]["type"] = "airport";
	$manualpagelist[15]["title"] = "World View";
	$manualpagelist[15]["type"] = "world";
	$manualpagelist[16]["title"] = "METAR Reader";
	$manualpagelist[16]["type"] = "metarreader";
	$manualpagelist[17]["title"] = "METAR Editor";
	$manualpagelist[17]["type"] = "metareditor";
	$manualpagelist[18]["title"] = "Flightplan Editor";
	$manualpagelist[18]["type"] = "flightplaneditor";
	$manualpagelist[19]["title"] = "KFreeFlight Configuration";
	$manualpagelist[19]["type"] = "config";
	$manualpagelist[20]["title"] = "FlightGear Path Configuration";
	$manualpagelist[20]["type"] = "config";
	$manualpagelist[21]["title"] = "FlightGear Configuration";
	$manualpagelist[21]["type"] = "config";
	$manualpagelist[22]["title"] = "Atlas Configuration";
	$manualpagelist[22]["type"] = "config";
	$manualpagelist[23]["title"] = "Advanced Configuration";
	$manualpagelist[23]["type"] = "config";
	$manualpagelist[24]["title"] = "KFreeFlight Calculator";
	$manualpagelist[24]["type"] = "calc";
	$manualpagelist[25]["title"] = "KFreeFlight Log Window";
	$manualpagelist[25]["type"] = "log";
	
	$currentmanualpage = 0;
	
?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
	<title>KFreeFlight</title>
	<meta name="AUTHOR" content="Didier Fabert">
	<meta http-equiv="Content-Script-Type" content="text/javascript">
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
	<link rel="stylesheet" type="text/css" href="./kfreeflight.css">
	<link rel="icon" type="image/x-icon" href="favicon.ico">
	<script type="text/javascript" src="./jquery-1.3.2.min.js"> </script>
	<script type="text/javascript" src="./jquery.li-scroller.1.0.js"> </script>
	<script type="text/javascript" src="./kfreeflight.js"> </script>
	<script type="text/javascript">
		var manualind = 0;
		var totalmanual = <?php echo count( $manualpagelist ); ?>;
		var totaltab = <?php echo count( $titlelist ); ?>;
		var manualtab = <?php echo $currentmanualpage; ?>;
		window.onload = function() { showTab(manualtab); $(function(){$('#ticker01').liScroll();});initSubtitle(); };
	</script>
</head>
<body>
	<div class="main">
		<?php
			printHeader();
			printLang( $langlist );
			printTicker( $tickerlist );
			printMenu( $titlelist );
			$text = "
				<img src=\"./img/tux.png\" width=\"150\" height=\"150\" alt=\"Tux : Linux inside\">
				<h3>What is it ?</h3>
				<p>
				KFreeFlight is a FlightGear GUI-frontend designed for KDE users. It can
				launch FlightGear with the most options without writting a very long
				command line.<br>
				It was made for GNU/Linux, but it may run on other *nix-like system (not-tested yet).
				</p>
				<p>
				This application is integrated as well as possible on the KDE environment, so KDE dependency will never be removed.
				</p>
				<p>
				A new version (for KDE4) is in the pipe, but no release was done yet. This version is only available with the subversion
				tool (SVN). This version is operationnal but a lot of work must be done before a release.
				</p>
				<h3>Disclaimer</h3>
				<p>
				All KFreeFlight tools musn't be use for real navigation. This application is made only for entertainment.
				</p>
				<p>
				<strong>Using KFreeFlight for aviation navigation is in fact illegal.</strong>
				</p>
				<h3>License</h3>
				<p>
				KFreeFlight is free software; you can redistribute it and/or modify it under the terms of the GNU
				General Public License as published by the Free Software Foundation, version 2.<br>
				This program is distributed in the hope that it will be useful,
				but WITHOUT ANY WARRANTY; without even the implied warranty of
				MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License (COPYING file) for
				more details.
				</p>
				<p>
				Actually, the application is available in languages :
				</p>
				<ul>
				<li>English</li>
				<li>French</li>
				<li>Italian</li>
				<li>German</li>
				</ul>\n";
			printTab( 0, $text );
			$text = "
				<p>Upper version</p>
				<ul>
				<li>Dev version are available via SVN</li>
				<li>Dev version are available via CVS (deprecated now)</li>
				</ul>
				<hr>
				<p>Ver 0.3.2-r2 Updated Dev release (2006-04-19)</p>
				<ul>
				<li><strong>Critic bugs fix</strong></li>
				</ul>
				<hr>
				<p>Ver 0.3.2 Updated Dev release (2006-04-16)</p>
				<ul>
				<li><strong>Need zlib, glut, plib-1.8.4 and simgear-0.3.10 libraries to compile</strong></li>
				<li><strong>KWeather and KWorldWatch (all in kde-toys package) must be installed</strong></li>
				<li>Add Aircraft 3D render thumbnail (by plib or simgear)</li>
				<li>Add KDE system tray integration option</li>
				<li>Fix some bugs</li>
				</ul>
				<hr>
				<p>Ver 0.3.1 Updated Dev release (2006-03-23)</p>
				<ul>
				<li><strong>Need zlib library to compile</strong></li>
				<li><strong>KWeather and KWorldWatch (all in kde-toys package) must be installed</strong></li>
				<li>Add real weather window : download the metar and make a report</li>
				<li>Add Find an airport by ICAO code, by name or coordinates window in the apt.dat.gz file and KWeather database</li>
				<li>Add personnal screen resolution (settable by the settings menu)</li>
				<li>Update multiplayer options</li>
				<li>Add lightning and precipitation rendering option</li>
				</ul>
				<hr>
				<p>Ver 0.2.1 - Updated Stable release (2006-03-01)</p>
				<ul>
				<li>Add shadows(aircraft, ai objects, scenery objects) options</li>
				<li>Add bump mapped clouds option</li>
				<li>Add reload aircraft list button</li>
				<li>Add ATC-Chatter option (FlightGear CVS)</li>
				</ul>
				<hr>
				<p>Ver 0.2 - First Stable release (2006-02-07)</p>
				<ul>
				<li>Adding GPS starting position</li>
				<li>Adding french language</li>
				<li>Fixing locale bug (locale with comma decimal point)</li>
				<li>Adding refresh button in toolbar</li>
				</ul>
				<hr>
				<p>Ver 0.1.4 - Dev release (2006-02-07)</p>
				<ul>
				<li>More than one config can be saved</li>
				<li>Adding a toolbar and a statusbar</li>
				<li>Carrier is now working</li>
				<li>You can choose your FlightGear executable file and pass it personnal parameters</li>
				<li>Adding Comm tab (in use and standby)</li>

				<li>Update Radio tab with NAV and ADF standby and adding TACAN</li>
				<li>Adding season (summer - winter)</li>
				<li>Adding Atlas settings</li>
				</ul>
				<hr>
				<p>Ver 0.1.2 - First Dev release (2006-01-18)</p>\n";
			printTab( 1, $text );
			$text = "
				<h3>Sources tarball</h3>
				<p>You can find it at <a
				href=\"http://sourceforge.net/project/showfiles.php?group_id=157130\">Sourceforge release
				repository</a></p>
				<h3>By distribution</h3>
				<p><strong>Don't have any hesitation, make package for your favorite GNU/Linux distribution.</strong></p>
				<p>The best way to share it is to upload package on a related website of your favorite distribution.<br />
				But don't forget to send us an email, and we put its path on the web site.</p>

				<p><strong>Available</strong></p>
				<ul>
				<li>Slackware package at 
				<a href=\"http://www.slacky.it/index.php?option=com_remository&amp;Itemid=1&amp;func=fileinfo&amp;filecatid=922&amp;parent=category\" target=\"new\">
				www.slacky.it</a> making by Andrea.</li>
				<li>Gentoo ebuild at <a href=\"http://bugs.gentoo.org/show_bug.cgi?id=125381\" target=\"new\">
					bugs.gentoo.org</a> making by Mauro.</li>

				<li> Suse 10.0 rpm package on <a href=\"http://home.tiscali.be/raoul.linux/downloadSuSE10.0.htm\">home.tiscali.be/raoul.linux</a> making by Raoul.</li>
				</ul>
				<h3>SVN Version</h3>
				<p>
				</p>
				<h4>Get a local copy</h4>
				<p>To check out a new copy of KFreeFlight from Subversion, open a terminal, cd into the directory where you want the new 
				KFreeFlight directory to be created and run the commands listed below. When prompted for the password, just press 
				the Enter key. The necessary commands are:</p>
				<p><strong>svn co https://kfreeflight.svn.sourceforge.net/svnroot/kfreeflight kfreeflight</strong></p>
				<p>And then :</p>
				<p><strong>cd kfreeflight</strong></p>
				<p><strong>mkdir build</strong></p>
				<p><strong>cd build</strong></p>
				<p><strong>cmake ..</strong></p>
				<p><strong>make</strong></p>
				<p><strong>make install</strong> as root</p>
				<h4>Update your SVN copy</h4>
				<p><strong>svn update</strong></p>
				<h3>CVS Version (deprecated)</h3>
				<p>A CVS version is now available<br /><a href=\"http://kfreeflight.cvs.sourceforge.net/kfreeflight/\" target=\"new\">
				CVS Web browser</a></p>

				<h4>Get a local copy</h4>
				<p>To check out a new copy of KFreeFlight from CVS, open a terminal, cd into the directory where you want the new 
				KFreeFlight directory to be created and run the commands listed below. When prompted for the password, just press 
				the Enter key. The necessary commands are:</p>
				<p><strong>cvs -d:pserver:anonymous@kfreeflight.cvs.sourceforge.net:/cvsroot/kfreeflight login</strong></p>
				<p><strong>cvs -z3 -d:pserver:anonymous@kfreeflight.cvs.sourceforge.net:/cvsroot/kfreeflight co -P kfreeflight</strong></p>
				<p>And then :</p>
				<p><strong>cd kfreeflight</strong></p>

				<p><strong>gmake -f Makefile.cvs</strong></p>
				<p><strong>./configure</strong></p>
				<p><strong>make</strong></p>
				<p><strong>make install</strong> as root</p>
				<h4>Update your CVS copy</h4>
				<p><strong>cvs update -dP</strong></p>\n";
			printTab( 2, $text );
			$text = "
				<h3>How send a bug report if I can't build the application ?</h3>
				<p>Send it by using the email address which is at the bottom of the TODO list section</p>
				<h3>Does KFreeFlight support the nice option for FlightGear executable ?</h3>

				<p>No. The &quot;nice -x fgfs&quot; executable doesn't make aircraft list.</p>
				<h3>Is it possible to remove the KDE dependency which make application more cross-platform?</h3>
				<p>No it's impossible : KFreeFlight was born because KDE haven't any launcher. I don't want to make a clone
				but offer something which is different and integrated as well as possible.
				<br />Otherwise I will NEVER change the code for the Redmond operating system which isn't a friendly platform for Open Source</p>
				<p>THINK DIFFERENT, THINK FREE</p>
				<h3>Why the 0.3.1 version is in the development branch ?</h3>

				<p>The application is stable but some features aren't enough tested, especially the weather report which may making a
				stable but false report.</p>
				<h3>Why have I an error when i dezip the tarball ?</h3>
				<p>You must dezip the tarball by taping <em>tar -xzf kfreeflight-&lt;version&gt;.tar.gz</em> in a terminal.<br />
				You couldn't using ark or anything else.</p>
				<h3>Why have I some warnings about aclocal ?</h3>
				<p>This part is in progress and appear because of an updated autoconf automake. Actually, this isn't a problem
				for building executable</p>
				<h3>Why the application's building fail in the linking stage ?</h3>
				<p>You can try <em>gmake -f Makefile.cvs</em> and relaunch the building process. If it's not solve the problem,
				send me a bug report.</p>
				<h3>I can see the splashscreen but the application crash after !</h3>
				<p>Relaunch the application (this part is in progress).<br />
				Some crash came because of false aircraft xml file (In that case change manually the number of aircraft in the config file :
				<em>/home/&lt;USER&gt;/.kfreeflight/&lt;Current config name&gt;</em></p>
				<h3>The splashscreen doesn't diseappear ! (v0.3.2 only)</h3>
				<p>This is a bug already reported : please download this file <a href=\"http://didier.fabert.free.fr/download/kfreeflight.cpp\">
				kfreeflight.cpp</a> and replace the older one in kfreeflight-0.3.2/src directory before relaunch the buiding process :<br />
				gmake -f Makefile.cvs &amp;&amp; ./configure &amp;&amp; make.<br />
				The 0.3.2-r2 release correct this problem.</p>
				<h3>There is no 3D render or thumbnail for the aircraft on the first launch ! (v0.3.2 only)</h3>
				<p>This is a bug already reported : before i can fix this problem, relaunch the application.<br />
				The 0.3.2-r2 release correct this problem.</p>\n";
			printTab( 3, $text );
			$text = "
				<h3>Mailing List : Devel</h3>
				<p>This is the good place for report problem (compilation, bugs, etc...), query a new feature or just taking about kfreeflight.</p>
				<h4>Subscribe</h4>
				<p><a href=\"https://lists.sourceforge.net/lists/listinfo/kfreeflight-devel\">Go to Subscribe page</a></p>

				<h4>Archives</h4>
				<p><a href=\"http://sourceforge.net/mailarchive/forum.php?forum=kfreeflight-devel\">Archived Messages</a></p>\n";
			printTab( 4, $text );
			$text = "
				<h3>Critic</h3>
				<ul><li>Correct my poor english in application and website.</li></ul>
				<p>But I can't do it myself and if someone can do it, contact me on the
				<a href=\"http://sourceforge.net/forum/forum.php?forum_id=528355\">developers forum</a></p>
				<h4>Otherwise, it rest a lot of things</h4>
				<ul>
				<li>Others languages traductions (need help)</li>
				<li>Finish and translate this web page (need help for translation)</li>
				<li>etc ...</li>
				</ul>
				<h3>How to translate KFreeFlight ?</h3>
				<p>This part is very simple : KFreeFlight put pot file in your \$KDE/share/apps/kfreeflight directory (min version 0.2).<br />
				Just open the <em>kfreeflight.pot</em> file with KBabel or another po file editor and rename it with locale and the <em>po</em> extention.<br />

				example : for french translation rename the file <em>fr.po</em><br />
				Now you can translate the application. Don't forget to send us this file at
				didier.fabert[-At-]gmail.com</p>
				<p>But it's a good idea to contact before, in case of someone else do the job. Don't forget to work
				with the lastest pot file in development ( taking it by subversion ).</p>\n";
			printTab( 5, $text );
				$page = "<div class=\"thumbnail\" id=\"manual0\">\n";
				$page .= "<div class=\"textinside\"><h3>Click on thumbnail to open the page</h3></div>\n";
				for( $i = 1 ; $i <= count ( $manualpagelist ) ; $i++)
				{
					$page .=  "<div class=\"nothingbutleft\">\n";
					$page .=  "<a href=\"#\" onClick=\"javascript:manualind=".$i.";showManual(manualind);\">\n";
					$page .= "<span class=\"thumbcontainer\">\n";
					$page .= "<img src=\"./img/thumbnails/screenshot".$i.".jpeg\" class=\"allthumb ".$manualpagelist[($i-1)]["type"]."thumb\" alt=\"KFF thumbnail\">\n";
					$page .= "</span>\n";
					$page .= "</a>\n";
					$page .=  "<p class=\"thumb\">".$manualpagelist[($i-1)]["title"]."</p>\n";
					$page .=  "</div>\n";
				}
				$page .= "</div>\n";
				$page .= "<div class=\"inside\" id=\"manualcontainer\">\n";
				$text = "
					<p>In general settings</p>\n
					<ul>\n
						<li>Splashscreen : let you see a splashscreen when FlightGear starting.</li>\n
						<li>Game mode : Launch FlightGear in true fullscreen mode.</li>\n
						<li>Fullscreen : Launch FlightGear in a maximised window.</li>\n
						<li>Intro music : let you ear a music at startup.</li>\n
						<li>Joystick : make joystick the main input device.</li>\n
						<li>Sound : enable sound in FlightGear.</li>\n
						<li>Auto-coordination : enable auto-coordination (usefull if you don't have a more than 3 axes joystick).</li>\n
						<li>Unit meter : The unit are in feet by default but you can overwrite this setting here</li>\n
					</ul>\n
					<p>In advanced settings</p>\n
					<ul>\n
						<li>NMEA protocol : usefull option for Atlas which let you see your position in real time.</li>\n
						<li>http server : Let you change flying values through a web browser. (by default : http://localhost:5500)</li>\n
						<li>Atlas too : launch Atlas and FlightGear together</li>\n
						<li>Wireframe and objects wireframe options : let you discover the FlightGear's internal world.</li>\n
						<li>Stop terrasync : By default, Terrasync will still running when FlightGear stop. You can stop it here.</li>\n
					</ul>\n";
				$page .= getManualPage(1, $manualpagelist, $text);
				$text = "
					<p>Rendering options</p>\n
					<ul>\n
						<li>Specular highlight : Enable specular reflections on textured objects</li>\n
						<li>Distance attenuation : Enable runway light distance attenuation</li>\n
						<li>Enhanced lightning : Enable enhanced runway lighting</li>\n
						<li>Clouds : Enable 2D (flat) cloud layers</li>\n
						<li>Cloud 3D : Enable 3D (volumetric) cloud layers</li>\n
						<li>Random objects : Include random scenery objects (buildings, etc.)</li>\n
						<li>Mouse pointer : Enable extra mouse pointer (i.e. for full screen Voodoo based cards)</li>\n
						<li>Sky blend : Enable sky blending</li>\n
						<li>Horizon effect : Enable celestial body growth illusion near the horizon</li>\n
						<li>Textures : Enable textures</li>\n
						<li>Lightning : Enable lightning rendering</li>\n
						<li>Precipitations : Enable precipitations endering</li>\n
						<li>AI traffic : Enable artificial intelligence traffic</li>\n
						<li>Wireframe : disable texturing</li>\n
					</ul>\n
					<p>Display resolution, shading and shadows</p>\n
					<ul>\n
						<li>You can choose here the screen resolution and the color depth. This is the place of your personnal screen resolution defined in the settings window.</li>\n
						<li>Shading : choose the shading level. Smooth is more beautiful, but need more processor ressource.</li>\n
						<li>Fog : choose the fog level. Nicest is more beautiful, but need more processor ressource.</li>\n
					</ul>\n";
				$page .= getManualPage(2, $manualpagelist, $text);
				$text = "";
				$page .= getManualPage(3, $manualpagelist, $text);
				$page .= getManualPage(4, $manualpagelist, $text);
				$page .= getManualPage(5, $manualpagelist, $text);
				$page .= getManualPage(6, $manualpagelist, $text);
				$page .= getManualPage(7, $manualpagelist, $text);
				$page .= getManualPage(8, $manualpagelist, $text);
				$page .= getManualPage(9, $manualpagelist, $text);
				$page .= getManualPage(10, $manualpagelist, $text);
				$page .= getManualPage(11, $manualpagelist, $text);
				$page .= getManualPage(12, $manualpagelist, $text);
				$page .= getManualPage(13, $manualpagelist, $text);
				$page .= getManualPage(14, $manualpagelist, $text);
				$page .= getManualPage(15, $manualpagelist, $text);
				$page .= getManualPage(16, $manualpagelist, $text);
				$page .= getManualPage(17, $manualpagelist, $text);
				$page .= getManualPage(18, $manualpagelist, $text);
				$page .= getManualPage(19, $manualpagelist, $text);
				$page .= getManualPage(20, $manualpagelist, $text);
				$page .= getManualPage(21, $manualpagelist, $text);
				$page .= getManualPage(22, $manualpagelist, $text);
				$page .= getManualPage(23, $manualpagelist, $text);
				$page .= getManualPage(24, $manualpagelist, $text);
				$page .= getManualPage(25, $manualpagelist, $text);
				$page .= getManualPage(26, $manualpagelist, $text);
				$page .= "<div class=\"cleared\">\n";
				$page .= "<span class=\"nothing\" id=\"nextenable\"><a href=\"#\" onClick=\"javascript:manualNext();\"><img src=\"./img/go-next.png\" alt=\"&nbsp;&lt;\"></a></span>\n";
				$page .= "<span class=\"nothing\" id=\"nextdisable\"><img src=\"./img/go-next-wb.png\" width=\"32\" height=\"32\" alt=\"&nbsp;&lt;\"></span>\n";
				$page .= "<span class=\"nothing\"><a href=\"#\" onClick=\"javascript:manualind=0;manualTop();\"><img src=\"./img/go-up.png\" alt=\"&nbsp;top&nbsp;\"></a></span>\n";
				$page .= "<span class=\"nothing\" id=\"prevenable\"><img src=\"./img/go-previous-wb.png\" width=\"32\" height=\"32\" alt=\"&gt;&nbsp;\"></span>\n";
				$page .= "<span class=\"nothing\" id=\"prevdisable\"><a href=\"#\" onClick=\"javascript:manualPrevious();\"><img src=\"./img/go-previous.png\" alt=\"&gt;&nbsp;\"></a></span>\n";
				$page .= "</div>\n";
				$page .= "</div>\n";
			printTab( 6, $page, true );
			$text = "
				<h3>Thanks to</h3>
				<ul>
				<li>Sourceforge which hosted KFreeFlight freely.</li>
				<li>G&eacute;rard for his help, his ideas and his aircraft models.</li>
				<li>Andrea who make italian translation and <a href=\"#getit\">Slackware Package</a>.</li>
				<li>Mauro who make <a href=\"#getit\">gentoo package</a>.</li>
				</ul>
				<p>If you think that you must be present in this part, contact the team on our
				<a href=\"http://sourceforge.net/forum/forum.php?forum_id=528355\" target=\"new\">forum</a>.</p>\n";
			printTab( 7, $text );
		?>
			
		<div class="logos" onClick="javascript:$('#rfid').show();">
<!--
			<a href="http://sourceforge.net/projects/kfreeflight" target="_blank">
				<img src="http://sflogo.sourceforge.net/sflogo.php?group_id=157130&amp;type=11" width="120" height="31"
					alt="Get KFreeFlight at SourceForge.net. Fast, secure and Free Open Source software downloads">
			</a>
			<a href="http://sourceforge.net" target="_blank">
			<a href="http://validator.w3.org/check?uri=referer" target="_blank">
				<img src="http://www.w3.org/Icons/valid-html401"
					alt="Valid HTML 4.01 Transitional" height="31" width="88">
			</a>
			<a href="http://jigsaw.w3.org/css-validator/check/referer" target="_blank">
				<img style="border:0;width:88px;height:31px"
					src="http://jigsaw.w3.org/css-validator/images/vcss" alt="CSS Valide !" />
			</a>
/-->
		</div>
	</div>
</body>
</html>