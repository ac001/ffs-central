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
		var totalmanual = 10;
		var totaltab = 8;
		var manualtab = 1;
		window.onload = function() { showTab(manualtab); $(function(){$('#ticker01').liScroll();}); };
	</script>
</head>
<body>
	<div class="main">
		<div class="header">
			<span class="headerleft"></span>
			<span class="headermiddle"><img src="./logo.png" class="logo" >&nbsp;KFreeFlight<!-- KFreeFl<img src="./tower.png" alt="OK">ght /--></span>
			<span class="headerright"></span>
		</div>
		<div class="language">
			<a class="lang" href="./index.php?lang=en" onMouseOver="javascript:$('#lang1').show();" onMouseOut="javascript:$('#lang1').hide();">
				<img src="./en.png" alt="en" class="flag">
			</a>
			<div class="viewercontainer langview" id="lang1">
				<div class="viewer">
					<p>English / American language</p>
				</div>
			</div>
			<a class="lang" href="./index.php?lang=fr" onMouseOver="javascript:$('#lang2').show();" onMouseOut="javascript:$('#lang2').hide();">
				<img src="./fr.png" alt="fr" class="flag">
			</a>
			<div class="viewercontainer langview" id="lang2">
				<div class="viewer">
					<p>French language</p>
				</div>
			</div>
			<a class="lang" href="./index.php?lang=it" onMouseOver="javascript:$('#lang3').show();" onMouseOut="javascript:$('#lang3').hide();">
				<img src="./it.png" alt="it" class="flag">
			</a>
			<div class="viewercontainer langview" id="lang3">
				<div class="viewer">
					<p>Italian language</p>
				</div>
			</div>
			<a class="lang" href="./index.php?lang=de" onMouseOver="javascript:$('#lang4').show();" onMouseOut="javascript:$('#lang4').hide();">
				<img src="./de.png" alt="de" class="flag">
			</a>
			<div class="viewercontainer langview" id="lang4">
				<div class="viewer">
					<p>German language</p>
				</div>
			</div>
		</div>
		<div class="ticker">
			<ul id="ticker01">
				<li><span><img src="./plane.png" alt="" width="68" height="18">01/01/2010</span><a href="#">A new SVN repository is available (KDE4 version)</a></li>
				<li><span><img src="./plane.png" alt="" width="68" height="18">01/01/2010</span><a href="#">CVS repository is out of date</a></li>
				<!-- eccetera -->
			</ul>
		</div>
		<div class="menu">
			<a href="#" class="tabmenu activated" onClick="javascript:manualtab=1;showTab(manualtab);">Introduction</a>
			<a href="#" class="tabmenu" onClick="javascript:manualtab=2;showTab(manualtab);">News</a>
			<a href="#" class="tabmenu" onClick="javascript:manualtab=3;showTab(manualtab);">Download</a>
			<a href="#" class="tabmenu" onClick="javascript:manualtab=4;showTab(manualtab);">FAQ</a>
			<a href="#" class="tabmenu" onClick="javascript:manualtab=5;showTab(manualtab);">Mailing List</a>
			<a href="#" class="tabmenu" onClick="javascript:manualtab=6;showTab(manualtab);">TODO</a>
			<a href="#" class="tabmenu" onClick="javascript:manualtab=7;showTab(manualtab);">Manual</a>
			<a href="#" class="tabmenu" onClick="javascript:manualtab=8;showTab(manualtab);">Thanks</a>
			&nbsp;<img src="./logo.png" class="logo" >
		</div>
		<div class="menubottom">
			<span class="bottommenu bottommenuinactive" id="menu1"></span>
			<span class="bottommenu bottommenuinactive" id="menu2"></span>
			<span class="bottommenu bottommenuinactive" id="menu3"></span>
			<span class="bottommenu bottommenuinactive" id="menu4"></span>
			<span class="bottommenu bottommenuinactive" id="menu5"></span>
			<span class="bottommenu bottommenuinactive" id="menu6"></span>
			<span class="bottommenu bottommenuinactive" id="menu7"></span>
			<span class="bottommenu bottommenuinactive" id="menu8"></span>
		</div>
		<div id="tab1" class="tabcontent">
			<div class="inside">
				<div class="textinside">
					<img src="./tux.png" width="150" height="150" alt="Tux : Linux inside">
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
					</ul>
				</div>
			</div>
		</div>
		<div id="tab2" class="tabcontent">
			<div class="inside">
				<div class="textinside">
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
					<p>Ver 0.1.2 - First Dev release (2006-01-18)</p>
				</div>
			</div>
		</div>
		<div id="tab3" class="tabcontent">
			<div class="inside">
				<div class="textinside">
					<h3>Sources tarball</h3>
					<p>You can find it at <a
					href="http://sourceforge.net/project/showfiles.php?group_id=157130">Sourceforge release
					repository</a></p>
					<hr>
					<h3>By distribution</h3>
					<p><strong>Don't have any hesitation, make package for your favorite GNU/Linux distribution.</strong></p>
					<p>The best way to share it is to upload package on a related website of your favorite distribution.<br />
					But don't forget to send us an email, and we put its path on the web site.</p>

					<p><strong>Available</strong></p>
					<ul>
					<li>Slackware package at 
					<a href="http://www.slacky.it/index.php?option=com_remository&amp;Itemid=1&amp;func=fileinfo&amp;filecatid=922&amp;parent=category" target="new">
					www.slacky.it</a> making by Andrea.</li>
					<li>Gentoo ebuild at <a href="http://bugs.gentoo.org/show_bug.cgi?id=125381" target="new">
						bugs.gentoo.org</a> making by Mauro.</li>

					<li> Suse 10.0 rpm package on <a href="http://home.tiscali.be/raoul.linux/downloadSuSE10.0.htm">home.tiscali.be/raoul.linux</a> making by Raoul.</li>
					</ul>
					<hr>
					<h3>SVN Version</h3>
					<p>
					</p>
					<hr>
					<h3>CVS Version (deprecated)</h3>
					<p>A CVS version is now available<br /><a href="http://kfreeflight.cvs.sourceforge.net/kfreeflight/" target="new">
					CVS Web browser</a></p>

					<h4>Get a local copy</h4>
					<p>To check out a new copy of KFreeFlight from CVS,open a terminal, cd into the directory where you want the new 
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
					<p><strong>cvs update -dP</strong></p>
				</div>
			</div>
		</div>
		<div id="tab4" class="tabcontent">
			<div class="inside">
				<div class="textinside">
					<p class="faqquestion">How send a bug report if I can't build the application ?</p>
					<p class="faqanswser">Send it by using the email address which is at the bottom of the TODO list section</p>
					<p class="faqquestion">Does KFreeFlight support the nice option for FlightGear executable ?</p>

					<p class="faqanswser">No. The &quot;nice -x fgfs&quot; executable doesn't make aircraft list.</p>
					<p class="faqquestion">Is it possible to remove the KDE dependency which make application more cross-platform?</p>
					<p class="faqanswser">No it's impossible : KFreeFlight was born because KDE haven't any launcher. I don't want to make a clone
					but offer something which is different and integrated as well as possible.
					<br />Otherwise I will NEVER change the code for the Redmond operating system which isn't a friendly platform for Open Source</p>
					<p class="faqanswser">THINK DIFFERENT, THINK FREE</p>
					<p class="faqquestion">Why the 0.3.1 version is in the development branch ?</p>

					<p class="faqanswser">The application is stable but some features aren't enough tested, especially the weather report which may making a
					stable but false report.</p>
					<p class="faqquestion">Why have I an error when i dezip the tarball ?</p>
					<p class="faqanswser">You must dezip the tarball by taping <em>tar -xzf kfreeflight-&lt;version&gt;.tar.gz</em> in a terminal.<br />
					You couldn't using ark or anything else.</p>

					<p class="faqquestion">Why have I some warnings about aclocal ?</p>
					<p class="faqanswser">This part is in progress and appear because of an updated autoconf automake. Actually, this isn't a problem
					for building executable</p>
					<p class="faqquestion">Why the application's building fail in the linking stage ?</p>
					<p class="faqanswser">You can try <em>gmake -f Makefile.cvs</em> and relaunch the building process. If it's not solve the problem,
					send me a bug report.</p>
					<p class="faqquestion">I can see the splashscreen but the application crash after !</p>

					<p class="faqanswser">Relaunch the application (this part is in progress).<br />
					Some crash came because of false aircraft xml file (In that case change manually the number of aircraft in the config file :
					<em>/home/&lt;USER&gt;/.kfreeflight/&lt;Current config name&gt;</em></p>
					<p class="faqquestion">The splashscreen doesn't diseappear ! (v0.3.2 only)</p>
					<p class="faqanswser">This is a bug already reported : please download this file <a href="http://didier.fabert.free.fr/download/kfreeflight.cpp">
					kfreeflight.cpp</a> and replace the older one in kfreeflight-0.3.2/src directory before relaunch the buiding process :<br />
					gmake -f Makefile.cvs &amp;&amp; ./configure &amp;&amp; make.<br />
					The 0.3.2-r2 release correct this problem.</p>
					<p class="faqquestion">There is no 3D render or thumbnail for the aircraft on the first launch ! (v0.3.2 only)</p>
					<p class="faqanswser">This is a bug already reported : before i can fix this problem, relaunch the application.<br />
					The 0.3.2-r2 release correct this problem.</p>
				</div>
			</div>
		</div>
		<div id="tab5" class="tabcontent">
			<div class="inside">
				<div class="textinside">
					<h3>Devel</h3>
						<p>This is the good place for report problem (compilation, bugs, etc...), query a new feature or just taking about kfreeflight.</p>
						<h3>Subscribe</h3>
						<p><a href="https://lists.sourceforge.net/lists/listinfo/kfreeflight-devel">Go to Subscribe page</a></p>

						<h3>Archives</h3>
						<p><a href="http://sourceforge.net/mailarchive/forum.php?forum=kfreeflight-devel">Archived Messages</a></p>
					<p>
					</p>
				</div>
			</div>
		</div>
		<div id="tab6" class="tabcontent">
			<div class="inside">
				<div class="textinside">
					<h3>Critic</h3>
					<ul><li>Correct my poor english in application and website.</li></ul>
					<p>But I can't do it myself and if someone can do it, contact me on the
						<a href="http://sourceforge.net/forum/forum.php?forum_id=528355">developers forum</a></p>
					<h3>Otherwise, it rest a lot of things</h3>
					<ul>
						<li>Others languages traductions (need help)</li>
						<li>Finish and translate this web page (need help for translation)</li>
						<li>etc ...</li>
					</ul>
					<h3>How to translate KFreeFlight ?</h3>
					<p>This part is very simple : KFreeFlight put pot file in your $KDE/share/apps/kfreeflight directory (min version 0.2).<br />
					Just open the <em>kfreeflight.pot</em> file with KBabel or another po file editor and rename it with locale and the <em>po</em> extention.<br />

					example : for french translation rename the file <em>fr.po</em><br />
					Now you can translate the application. Don't forget to send us this file at
					didier.fabert[-At-]gmail.com</p>
					<p>But it's a good idea to contact before, in case of someone else do the job. Don't forget to work
					with the lastest pot file in development ( taking it by subversion ).</p>
				</div>
			</div>
		</div>
		<div id="tab7" class="tabcontent">
			<div class="thumbnail" id="manual0">
				<div class="textinside"><h3>Click on thumbnail to open the page</h3></div>
				<div class="nothingbutleft">
					<a href="#" onClick="javascript:manualind=1;showManual(manualind);"><img src="./tux.png" class="thumb" alt="KFF thumbnail"></a>
					<p class="thumb">Page 1</p>
				</div>
				<div class="nothingbutleft">
					<a href="#" onClick="javascript:manualind=2;showManual(manualind);"><img src="./tux.png" class="thumb" alt="KFF thumbnail"></a>
					<p class="thumb">Page 2</p>
				</div>
				<div class="nothingbutleft">
					<a href="#" onClick="javascript:manualind=3;showManual(manualind);"><img src="./tux.png" class="thumb" alt="KFF thumbnail"></a>
					<p class="thumb">Page 3</p>
				</div>
				<div class="nothingbutleft">
					<a href="#" onClick="javascript:manualind=4;showManual(manualind);"><img src="./tux.png" class="thumb" alt="KFF thumbnail"></a>
					<p class="thumb">Page 4</p>
				</div>
				<div class="nothingbutleft">
					<a href="#" onClick="javascript:manualind=5;showManual(manualind);"><img src="./tux.png" class="thumb" alt="KFF thumbnail"></a>
					<p class="thumb">Page 5</p>
				</div>
				<div class="nothingbutleft">
					<a href="#" onClick="javascript:manualind=6;showManual(manualind);"><img src="./tux.png" class="thumb" alt="KFF thumbnail"></a>
					<p class="thumb">Page 6</p>
				</div>
				<div class="nothingbutleft">
					<a href="#" onClick="javascript:manualind=7;showManual(manualind);"><img src="./tux.png" class="thumb" alt="KFF thumbnail"></a>
					<p class="thumb">Page 7</p>
				</div>
				<div class="nothingbutleft">
					<a href="#" onClick="javascript:manualind=8;showManual(manualind);"><img src="./tux.png" class="thumb" alt="KFF thumbnail"></a>
					<p class="thumb">Page 8</p>
				</div>
				<div class="nothingbutleft">
					<a href="#" onClick="javascript:manualind=9;showManual(manualind);"><img src="./tux.png" class="thumb" alt="KFF thumbnail"></a>
					<p class="thumb">Page 9</p>
				</div>
				<div class="nothingbutleft">
					<a href="#" onClick="javascript:manualind=10;showManual(manualind);"><img src="./tux.png" class="thumb" alt="KFF thumbnail"></a>
					<p class="thumb">Page 10</p>
				</div>
			</div>
			<div class="inside" id="manualcontainer">
				<div id="manual1" class="textinside">
					<a href="#" onClick="javascript:$('#app1').show();">
						<span class="zoom">
							<img src="./tux.png" class="thumb" alt="KFF thumbnail">
							Click to enlarge
							<img src="./zoom.png" class="zoom" alt="Zoom">
						</span>
					</a>
					<h3>General Tab</h3>
					<p>In general settings</p>
					<ul>
						<li>Splashscreen : let you see a splashscreen when FlightGear starting.</li>
						<li>Game mode : Launch FlightGear in true fullscreen mode.</li>
						<li>Fullscreen : Launch FlightGear in a maximised window.</li>
						<li>Intro music : let you ear a music at startup.</li>
						<li>Joystick : make joystick the main input device.</li>
						<li>Unit meter : The unit are in feet by default but you can overwrite this setting here</li>
					</ul>
					<p>In advanced settings</p>
					<ul>
						<li>NMEA protocol : usefull option for Atlas which let you see your position in real time.</li>
						<li>http server : Let you change flying values through a web browser. (by default : http://localhost:5500)</li>
						<li>Atlas too : launch Atlas and FlightGear together</li>
						<li>Wireframe and objects wireframe options : let you discover the FlightGear's internal world.</li>
					</ul>
					<div class="viewercontainer appview" id="app1" onClick="javascript:$('#app1').hide();">
						<div class="viewer">
							<h1>Page 1</h1>
							<img src="./tux.png" class="appview" alt="KFF thumbnail">
							<p>Click on the window to close it</p>
						</div>
					</div>
				</div>
				<div id="manual2" class="textinside">
					<a href="#" onClick="javascript:$('#app2').show();">
						<span class="zoom">
							<img src="./tux.png" class="thumb" alt="KFF thumbnail">
							Click to enlarge
							<img src="./zoom.png" class="zoom" alt="Zoom">
						</span>
					</a>
					<h3>Render Tab</h3>
					<p>Rendering options</p>
					<ul>
						<li>Specular highlight : Enable specular reflections on textured objects</li>
						<li>Distance attenuation : Enable runway light distance attenuation</li>
						<li>Enhanced lightning : Enable enhanced runway lighting</li>
						<li>Clouds : Enable 2D (flat) cloud layers</li>
						<li>Bump mapped clouds : </li>
						<li>Cloud 3D : Enable 3D (volumetric) cloud layers</li>
						<li>Random objects : Include random scenery objects (buildings, etc.)</li>
						<li>Mouse pointer : Enable extra mouse pointer (i.e. for full screen Voodoo based cards)</li>
						<li>Sky blend : Enable sky blending</li>
						<li>Horizon effect : Enable celestial body growth illusion near the horizon</li>
						<li>Textures : Enable textures</li>
						<li>Lightning : Enable lightning rendering</li>
						<li>Precipitations : Enable precipitations endering</li>
					</ul>
					<p>Display resolution, shading and shadows</p>
					<ul>
						<li>You can choose here the screen resolution and the color depth. This is the place of your personnal screen resolution defined 
						in the settings window.</li>
						<li>Shading : choose the shading level. Smooth is more beautiful, but need more processor ressource.</li>
						<li>Shadows : choose the objects which must have a shadow (plane, transparency: plane have shadow on ground only, 
						scenery objects, ai objects)</li>
					</ul>
					<div class="viewercontainer appview" id="app2" onClick="javascript:$('#app2').hide();">
						<div class="viewer">
							<h1>Page 2</h1>
							<img src="./tux.png" class="appview" alt="KFF thumbnail">
							<p>Click on the window to close it</p>
						</div>
					</div>
				</div>
				<div id="manual3" class="textinside">
					<a href="#" onClick="javascript:$('#app3').show();">
						<span class="zoom">
							<img src="./tux.png" class="thumb" alt="KFF thumbnail">
							Click to enlarge
							<img src="./zoom.png" class="zoom" alt="Zoom">
						</span>
					</a>
					<h3>Page 3</h3>
					<div class="viewercontainer appview" id="app3" onClick="javascript:$('#app3').hide();">
						<div class="viewer">
							<h1>Page 3</h1>
							<img src="./tux.png" class="appview" alt="KFF thumbnail">
							<p>Click on the window to close it</p>
						</div>
					</div>
				</div>
				<div id="manual4" class="textinside">
					<a href="#" onClick="javascript:$('#app4').show();">
						<span class="zoom">
							<img src="./tux.png" class="thumb" alt="KFF thumbnail">
							Click to enlarge
							<img src="./zoom.png" class="zoom" alt="Zoom">
						</span>
					</a>
					<h3>Page 4</h3>
					<div class="viewercontainer appview" id="app4" onClick="javascript:$('#app4').hide();">
						<div class="viewer">
							<h1>Page 4</h1>
							<img src="./tux.png" class="appview" alt="KFF thumbnail">
							<p>Click on the window to close it</p>
						</div>
					</div>
				</div>
				<div id="manual5" class="textinside">
					<a href="#" onClick="javascript:$('#app5').show();">
						<span class="zoom">
							<img src="./tux.png" class="thumb" alt="KFF thumbnail">
							Click to enlarge
							<img src="./zoom.png" class="zoom" alt="Zoom">
						</span>
					</a>
					<h3>Page 5</h3>
					<div class="viewercontainer appview" id="app5" onClick="javascript:$('#app5').hide();">
						<div class="viewer">
							<h1>Page 5</h1>
							<img src="./tux.png" class="appview" alt="KFF thumbnail">
							<p>Click on the window to close it</p>
						</div>
					</div>
				</div>
				<div id="manual6" class="textinside">
					<a href="#" onClick="javascript:$('#app6').show();">
						<span class="zoom">
							<img src="./tux.png" class="thumb" alt="KFF thumbnail">
							Click to enlarge
							<img src="./zoom.png" class="zoom" alt="Zoom">
						</span>
					</a>
					<h3>Page 6</h3>
					<div class="viewercontainer appview" id="app6" onClick="javascript:$('#app6').hide();">
						<div class="viewer">
							<h1>Page 6</h1>
							<img src="./tux.png" class="appview" alt="KFF thumbnail">
							<p>Click on the window to close it</p>
						</div>
					</div>
				</div>
				<div id="manual7" class="textinside">
					<a href="#" onClick="javascript:$('#app7').show();">
						<span class="zoom">
							<img src="./tux.png" class="thumb" alt="KFF thumbnail">
							Click to enlarge
							<img src="./zoom.png" class="zoom" alt="Zoom">
						</span>
					</a>
					<h3>Page 7</h3>
					<div class="viewercontainer appview" id="app7" onClick="javascript:$('#app7').hide();">
						<div class="viewer">
							<h1>Page 7</h1>
							<img src="./tux.png" class="appview" alt="KFF thumbnail">
							<p>Click on the window to close it</p>
						</div>
					</div>
				</div>
				<div id="manual8" class="textinside">
					<a href="#" onClick="javascript:$('#app8').show();">
						<span class="zoom">
							<img src="./tux.png" class="thumb" alt="KFF thumbnail">
							Click to enlarge
							<img src="./zoom.png" class="zoom" alt="Zoom">
						</span>
					</a>
					<h3>Page 8</h3>
					<div class="viewercontainer appview" id="app8" onClick="javascript:$('#app8').hide();">
						<div class="viewer">
							<h1>Page 8</h1>
							<img src="./tux.png" class="appview" alt="KFF thumbnail">
							<p>Click on the window to close it</p>
						</div>
					</div>
				</div>
				<div id="manual9" class="textinside">
					<a href="#" onClick="javascript:$('#app9').show();">
						<span class="zoom">
							<img src="./tux.png" class="thumb" alt="KFF thumbnail">
							Click to enlarge
							<img src="./zoom.png" class="zoom" alt="Zoom">
						</span>
					</a>
					<h3>Page 9</h3>
					<div class="viewercontainer appview" id="app9" onClick="javascript:$('#app9').hide();">
						<div class="viewer">
							<h1>Page 9</h1>
							<img src="./tux.png" class="appview" alt="KFF thumbnail">
							<p>Click on the window to close it</p>
						</div>
					</div>
				</div>
				<div id="manual10" class="textinside">
					<a href="#" onClick="javascript:$('#app10').show();">
						<span class="zoom">
							<img src="./tux.png" class="thumb" alt="KFF thumbnail">
							Click to enlarge
							<img src="./zoom.png" class="zoom" alt="Zoom">
						</span>
					</a>
					<h3>Page 10</h3>
					<div class="viewercontainer appview" id="app10" onClick="javascript:$('#app10').hide();">
						<div class="viewer">
							<h1>Page 10</h1>
							<img src="./tux.png" class="appview" alt="KFF thumbnail">
							<p>Click on the window to close it</p>
						</div>
					</div>
				</div>
				<div class="cleared">
					<span class="nothing" id="nextenable"><a href="#" onClick="javascript:manualNext();"><img src="./go-next.png" alt="&nbsp;&lt;"></a></span>
					<span class="nothing" id="nextdisable"><img src="./go-next-wb.png" width="32" height="32" alt="&nbsp;&lt;"></span>
					<span class="nothing"><a href="#" onClick="javascript:manualind=0;manualTop();"><img src="./go-up.png" alt="&nbsp;top&nbsp;"></a></span>
					<span class="nothing" id="prevenable"><img src="./go-previous-wb.png" width="32" height="32" alt="&gt;&nbsp;"></span>
					<span class="nothing" id="prevdisable"><a href="#" onClick="javascript:manualPrevious();"><img src="./go-previous.png" alt="&gt;&nbsp;"></a></span>
				</div>
			</div>
		</div>
		<div id="tab8" class="tabcontent">
			<div class="inside">
			<p>Thanks to</p>
			<ul>
				<li>Sourceforge which hosted KFreeFlight freely.</li>
				<li>G&eacute;rard for his help, his ideas and his aircraft models.</li>
				<li>Andrea who make italian translation and <a href="#getit">Slackware Package</a>.</li>
				<li>Mauro who make <a href="#getit">gentoo package</a>.</li>
			</ul>
			<p>If you think that you must be present in this part, contact the team on our
			<a href="http://sourceforge.net/forum/forum.php?forum_id=528355" target="new">forum</a>.</p>
			</div>
		</div>
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
			</a> /-->
		</div>
		<!--
		<div class="viewercontainer" id="rfid" onClick="javascript:$('#rfid').hide();">
			<div class="viewer">
				<h1>RFID tag</h1>
				<img src="./rfid.png" alt="RFID">
				<p>Click on the window to close it</p>
			</div>
		</div> /-->
	</div>
</body>
</html>