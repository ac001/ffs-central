function showManual(clicked)
{
	if( clicked < 0 )
	{
		for ( var i = 0 ; i <= totalmanual ; i++)
		{
			$('#manual'+i).hide();
		}
		$('#manualcontainer').hide();
		return;
	}
	for ( var i = 0 ; i <= totalmanual ; i++)
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
		if ( manualind == totalmanual )
		{
			// Grey the next button
			$('#nextenable').hide();
			$('#nextdisable').show();
		}
		else
		{
			// Grey the next button
			$('#nextenable').show();
			$('#nextdisable').hide();
		}
		if ( manualind == 1 )
		{
			// Grey the previous button
			$('#prevenable').show();
			$('#prevdisable').hide();
		}
		else
		{
			// Grey the next button
			$('#prevenable').hide();
			$('#prevdisable').show();
		}
	}
}
function showTab(clicked)
{
	for ( var i = 0 ; i < totaltab ; i++)
	{
		if (i == clicked)
		{
			$('#tab'+i).show();
			$('#menu'+i).removeClass('bottommenuinactive');
			$('#menu'+i).addClass('bottommenuactive');
			if (i == manualtab)
			{
				showManual(0);
			}
			else
			{
				showManual(-1);
			}
		}
		else
		{
			$('#tab'+i).hide();
			$('#menu'+i).removeClass('bottommenuactive');
			$('#menu'+i).addClass('bottommenuinactive');
		}
	}
}
function initSubtitle()
{
	var wi, to, tm;
	wi = $('a.tabmenu').css( 'width' );
	wi = wi.substr( 0, wi.length - 2 );
	tm = $('a.tabmenu').css( 'height' );
	tm = tm.substr( 0, tm.length - 2 );
	to = $('a.tabmenu').offset().top;
	to = parseInt( tm, 10 ) + parseInt( to , 10 ) - 10;
	for ( var i = 0 ; i < totaltab ; i++)
	{
		$('#sub'+i).css( 'left', ( wi * i ) + "px" );
		$('#sub'+i).css( 'top', to + "px" );
	}
}
function manualNext()
{
	if ( manualind < totalmanual )
	{
		manualind++;
		showManual(manualind);
	}
}
function manualPrevious()
{
	if ( manualind > 1 )
	{
		manualind--;
		showManual(manualind);
	}
}
function manualTop()
{
	manualind = 0;
	showManual(manualind);
}
function moveSubtitle(id)
{
	alert(subid);
}
