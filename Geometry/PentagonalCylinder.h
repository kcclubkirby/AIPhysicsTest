class PentagonalCylinder : public TriangleMesh3D
{
private:
	Vector3D vertex[10] ;

public:
	PentagonalCylinder()
	{
		vertex[0][X] = 100 ; vertex[1][X] = 100 ;
		vertex[0][Y] = 100 ; vertex[1][Y] = 200 ;
		vertex[0][Z] = 200 ; vertex[1][Z] = 200 ;

		vertex[2][X] = 200 ; vertex[3][X] = 200 ;
		vertex[2][Y] = 100 ; vertex[3][Y] = 200 ;
		vertex[2][Z] = 100 ; vertex[3][Z] = 100 ;

		vertex[4][X] = 300 ; vertex[5][X] = 300 ;
		vertex[4][Y] = 100 ; vertex[5][Y] = 200 ;
		vertex[4][Z] = 100 ; vertex[5][Z] = 100 ;

		vertex[6][X] = 400 ; vertex[7][X] = 400 ;
		vertex[6][Y] = 100 ; vertex[7][Y] = 200 ;
		vertex[6][Z] = 200 ; vertex[7][Z] = 200 ;

		vertex[8][X] = 250 ; vertex[9][X] = 250 ;
		vertex[8][Y] = 100 ; vertex[9][Y] = 200 ;
		vertex[8][Z] = 350 ; vertex[9][Z] = 350 ;

		Add_Triangle( Triangle3D( vertex[1], vertex[2], vertex[0] ) ) ;
		Add_Triangle( Triangle3D( vertex[2], vertex[1], vertex[3] ) ) ;

		Add_Triangle( Triangle3D( vertex[2], vertex[3], vertex[4] ) ) ;
		Add_Triangle( Triangle3D( vertex[4], vertex[3], vertex[5] ) ) ;

		Add_Triangle( Triangle3D( vertex[4], vertex[5], vertex[6] ) ) ;
		Add_Triangle( Triangle3D( vertex[6], vertex[5], vertex[7] ) ) ;

		Add_Triangle( Triangle3D( vertex[6], vertex[7], vertex[8] ) ) ;
		Add_Triangle( Triangle3D( vertex[8], vertex[7], vertex[9] ) ) ;

		Add_Triangle( Triangle3D( vertex[8], vertex[9], vertex[0] ) ) ;
		Add_Triangle( Triangle3D( vertex[0], vertex[9], vertex[1] ) ) ;
	}
} ;	// PentagonalCylinder