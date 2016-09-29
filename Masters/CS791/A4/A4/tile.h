using namespace std;

struct transfrm{
	float a;
	float b;
	float c;
	float d;
	float e;
	float f;
};

struct translation{
	float x;
	float y;
};

struct vertex{
	float x;
	float y;
	float contact;
};

struct line {
	vertex midpoint;
	vertex controlpoint;
};

struct intersection {
	line leftOutside;
	line leftInside;
	line rightInside;
	line rightOutside;
	vertex topIntersection;
	vertex bottomIntersection;
	float distance;
};

bool operator==(const vertex &v1, const vertex v2){
	return v1.x == v2.x && v1.y == v2.y;
}


bool operator==(const line &l1, const line l2){
	return l1.midpoint == l2.midpoint && l1.controlpoint == l2.controlpoint;
}

class tile{

	public:

		string _type;
		int _sides;

		vector<vertex> _vertices;

		vector<transfrm> _transforms;


		tile(string type){
			_type = type;
		}

		void tile::addTransform(transfrm t){
			_transforms.push_back(t);
		}

		void tile::addVertex(vertex v){
			_vertices.push_back(v);
		}

};


class tiling{

	public:


		string _type;
		vector<translation> _translations;
		vector<tile*> _tiles;

		tiling(string type){
			_type = type;
		}

		~tiling(){
			for (int i = 0; i < _tiles.size(); i++){
				delete _tiles[i];
			}
		}

		void tiling::addTranslation(translation t){
			_translations.push_back(t);
		}

		void tiling::addTile(tile *t){
			_tiles.push_back(t);
		}

};