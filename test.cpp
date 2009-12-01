#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

int main()
{
// Initialisation de l'environnement XPath
	xmlXPathInit();
// Cr�ation du contexte
	xmlXPathContextPtr ctxt = xmlXPathNewContext( doc ); // doc est un xmlDocPtr repr�sentant notre catalogue

	if ( ctxt == NULL )
	{
		fprintf( stderr, "Erreur lors de la cr�ation du contexte XPath\n" );
		exit( -1 );
	}

// Evaluation de l'expression XPath
	xmlXPathObjectPtr xpathRes = xmlXPathEvalExpression( "/catalogue/produit[prix<10]/intitule/text()", ctxt );

	if ( xpathRes == NULL )
	{
		fprintf( stderr, "Erreur sur l'expression XPath\n" );
		exit( -1 );
	}

// Manipulation du r�sultat
	if ( xpathRes->type == XPATH_NODESET )
	{
		int i;
		printf( "Produits dont le prix est inf�rieur � 10 Euros :\n" );

		for ( i = 0; i < xpathRes->nodesetval->nodeNr; i++ )
		{
			xmlNodePtr n = xpathRes->nodesetval->nodeTab[i];

			if ( n->type == XML_TEXT_NODE || n->type == XML_CDATA_SECTION_NODE )
			{
				printf( "- %s\n", n->content );
			}
		}
	}

// Lib�ration de la m�moire
	xmlXPathFreeObject( xpathRes );

	xmlXPathFreeContext( ctxt );
}
