function showManual(clicked, total)
{
	for ( var i = 0 ; i <= total ; i++)
	{
		if (i == clicked)
		{
			$('#manual'+i).show();
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
}
$(function()
{
	$('#ticker01').liScroll();
});