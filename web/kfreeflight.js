function showTab(clicked, nbtab)
{
	for ( i = 1 ; i < nbtab ; i++)
	{
		if (i == clicked)
		{
			$('#tab'+i).show();
			$('#menu'+i).removeClass('bottommenuinactive');
			$('#menu'+i).addClass('bottommenuactive');
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