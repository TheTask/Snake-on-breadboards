#ifdef FALSE
#include <conio.h>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <windows.h>

using namespace std;

#define VYSKAPLOCHY 20
#define SIRKAPLOCHY 50
#define POCIATOCNADLZKAHADA 3
#define FPS 10

struct ClanokHada
{
	ClanokHada(){}
	ClanokHada( short x1,short y1 )
	{
		x = x1;
		y = y1;
	}
	short x;
	short y;
};

unsigned short dlzkaHada = POCIATOCNADLZKAHADA;
char poslednySmer = 'd';
vector< ClanokHada > m_Had;

unsigned short xPotrava;
unsigned short yPotrava;

char plocha[ VYSKAPLOCHY * SIRKAPLOCHY ];

const void ZobrazPlochu();
void NormalizujPlochu();
const void InicializujHada();
const void InicializujPotravu();
void Pohyb();
void ZmazKoniecHada();
bool ZozralPotravu();

void VycistiKonzolu();

bool Vyhral();
bool Prehral();

inline bool operator==( const ClanokHada &lavaStrana,const ClanokHada &pravaStrana );

int main()
{
	srand( (unsigned int)time( NULL ) );

	NormalizujPlochu();
	InicializujHada();
	InicializujPotravu();

	for( ;; )
	{
		clock_t start;
		double cas = 0.0;
		start = clock();

		while( cas < 1.0 / FPS )
		{
			cas = ( clock() - start ) / (double)CLOCKS_PER_SEC;
		}

		if( _kbhit() )
		{
			poslednySmer = _getch();
		}
		
		if( ZozralPotravu() ) 
		{
			dlzkaHada++;
			ClanokHada clanok( xPotrava,yPotrava );
			m_Had.push_back( clanok );
			InicializujPotravu();
		}

		VycistiKonzolu();
		ZobrazPlochu();
		Pohyb();

		if( Vyhral() )
		{
			printf( "Gratulujem, vyhral si!\n" );
		}
		if( Prehral() )
		{
			printf( "Prehral si!\n" );
			break;
		}
	}
	system( "PAUSE" );
}
const void ZobrazPlochu() DONE
{
	for( unsigned short i = 0; i < SIRKAPLOCHY + 2; i++ ) printf( "%c",'/' ); printf( "\n" ); //horna hranica

	for( unsigned short y = 0; y < VYSKAPLOCHY; y++ )
	{
		printf( "%c",'/' );
		for( unsigned short x = 0; x < SIRKAPLOCHY; x++ )
		{
			printf( "%c",plocha[ y * SIRKAPLOCHY + x ] );
		}
		printf( "%c\n",'/' );
	}
	
	for( unsigned short i = 0; i < SIRKAPLOCHY + 2; i++ ) printf( "%c",'/' ); printf( "\n" ); //spodna hranica	
	printf( "Dlzka hada: %d\n",dlzkaHada );
}
void NormalizujPlochu() DONE
{
	for( unsigned short x = 0; x < SIRKAPLOCHY; x++ )
	{
		for( unsigned short y = 0; y < VYSKAPLOCHY; y++ )
		{
			 plocha[ y * SIRKAPLOCHY + x ] = ' ';
		}
	}
}
const void InicializujHada()
{
	for( unsigned short i = 0; i < dlzkaHada; i++ )
	{
		ClanokHada clanok;
		clanok.x = i;
		clanok.y = 0;
		m_Had.push_back( clanok );
		plocha[ i ] = 'O';
	}
}
const void InicializujPotravu()
{
	xPotrava = rand() % SIRKAPLOCHY;
	yPotrava = rand() % VYSKAPLOCHY;

	while( plocha[ yPotrava * SIRKAPLOCHY + xPotrava ] != ' ' )
	{
		xPotrava = rand() % SIRKAPLOCHY;
		yPotrava = rand() % VYSKAPLOCHY;
	}

	plocha[ yPotrava * SIRKAPLOCHY + xPotrava ] = 'X'; 
}
void Pohyb()
{
	if( poslednySmer == 'd' )
	{
		ClanokHada clanok = m_Had.at( m_Had.size() - 1 ); //posledny clanok je vlastne prvy
		clanok.x++;
		m_Had.push_back( clanok );
		plocha[ clanok.y * SIRKAPLOCHY + clanok.x ] = 'O';

		ZmazKoniecHada();
	}
	else if( poslednySmer == 's' )
	{
		ClanokHada clanok = m_Had.at( m_Had.size() - 1 ); 
		clanok.y++;
		m_Had.push_back( clanok );
		plocha[ clanok.y * SIRKAPLOCHY + clanok.x ] = 'O';

		ZmazKoniecHada();
	}
	else if( poslednySmer == 'a' )
	{
		ClanokHada clanok = m_Had.at( m_Had.size() - 1 ); 
		clanok.x--;
		m_Had.push_back( clanok );
		plocha[ clanok.y * SIRKAPLOCHY + clanok.x ] = 'O';

		ZmazKoniecHada();
	}
	else if( poslednySmer == 'w' )
	{
		ClanokHada clanok = m_Had.at( m_Had.size() - 1 ); 
		clanok.y--;
		m_Had.push_back( clanok );
		plocha[ clanok.y * SIRKAPLOCHY + clanok.x ] = 'O';

		ZmazKoniecHada();
	}
	else
	{}

}
void ZmazKoniecHada()
{
	ClanokHada temp = m_Had[ 0 ]; //prvy je vlastne posledny
	plocha[ temp.y * SIRKAPLOCHY + temp.x ] = ' ';
	m_Had.erase( m_Had.begin() );
}
bool ZozralPotravu()
{
	ClanokHada clanok = m_Had.at( m_Had.size() - 1 );
	ClanokHada potrava;
	potrava.x = xPotrava;
	potrava.y = yPotrava;
	return clanok == potrava;
}
void VycistiKonzolu()
{
	HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	COORD coord = { 0,0 };
	DWORD count;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if( GetConsoleScreenBufferInfo( hStdOut,&csbi ) )
	{
		FillConsoleOutputCharacter( hStdOut,(TCHAR)32,csbi.dwSize.X * csbi.dwSize.Y,coord,&count );
		FillConsoleOutputAttribute( hStdOut,csbi.wAttributes,csbi.dwSize.X - 1* csbi.dwSize.Y - 1,coord,&count );
		SetConsoleCursorPosition( hStdOut,coord );
	}
	return;
}
bool Vyhral()
{
	bool medzera = false;
	for( unsigned short x = 0; x < SIRKAPLOCHY; x++ )
	{
		for( unsigned short y = 0; y < VYSKAPLOCHY; y++ )
		{
			 if( plocha[ y * SIRKAPLOCHY + x ] == ' ' )
			 {
				medzera = true;
				break;
			 }
		}
	}
	return !medzera;
}
bool Prehral()
{
	ClanokHada clanok = m_Had.at( m_Had.size() - 1 );

	if( clanok.x < 0 || 
		clanok.x > SIRKAPLOCHY - 1 || 
		clanok.y < 0 ||
		clanok.y > VYSKAPLOCHY - 1 ) return true;
	
	for( unsigned short i = 0; i < m_Had.size() - 1; i++ )
	{
		ClanokHada temp = m_Had[ i ];
		if( temp == clanok ) return true;
	}

	return false;
}
inline bool operator==( const ClanokHada &lavaStrana,const ClanokHada &pravaStrana )
{
	return lavaStrana.x == pravaStrana.x && lavaStrana.y == pravaStrana.y;
}

#endif