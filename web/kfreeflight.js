function showManual(clicked, total)
{
	for ( var i = 0 ; i <= total ; i++)
	{
		if (i == clicked)
		{
			$('#manual'+i).show();
			if ( i == 0 )
			{
				$('#manualcontainer').hide();
			}
			else
			{
				$('#manualcontainer').show();
			}
		}
		else
		{
			$('#manual'+i).hide();
		}
	}
}
function showTab(clicked, total, maxmanual)
{
	for ( var i = 1 ; i <= total ; i++)
	{
		if (i == clicked)
		{
			$('#tab'+i).show();
			$('#menu'+i).removeClass('bottommenuinactive');
			$('#menu'+i).addClass('bottommenuactive');
			if (i == 4)
			{
				showManual(0,maxmanual);
			}
		}
		else
		{
			$('#tab'+i).hide();
			$('#menu'+i).removeClass('bottommenuactive');
			$('#menu'+i).addClass('bottommenuinactive');
		}
	}
	$('#debug').text("val="+clicked+" total="+total+" maxmanual="+maxmanual);
}
function manualNext(ind, total)
{
	if ( ind < total )
	{
		ind++;
		showManual(ind, total);
	}
	else
	{
		deb="error";
	}
	$('#debug').text(deb+", ind="+ind+", total="+total);
}
function manualPrevious(ind, total)
{
	if ( ind > 1 )
	{
		ind--;
		showManual(ind, total);
	}
	else
	{
		deb="error";
	}
	$('#debug').text(deb+", ind="+ind+", total="+total);
}
function manualTop(ind, total)
{
	ind = 0;
	showManual(ind, total);
	$('#debug').text("ind="+ind+" total="+total);
}
$(function()
{
	$('#ticker01').liScroll();
});