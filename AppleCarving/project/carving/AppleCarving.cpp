#include "AppleCarving/AppleCarving.hpp"
#define CGAL_USE_BASIC_VIEWER

Cities::Cities()
{

};

Cities::~Cities()
{

};

void Cities::getCount(std::string path)
{	
	int c = 0;
	std::string ch;
	std::fstream file;
	file.open(path);
	std::string temp;
	if (file.is_open())
		while (std::getline(file, ch))
			c++;
	this->count = c;
};

void Cities::getCoordinate(std::string path)
{

	getCount(path);
	this->coordinate.resize(this->count); 

	char ch;
	int temp = 0;
	int sh = 0;
	std::fstream file;
	file.open(path);
	if (file.is_open())
		while (file.get(ch))
		{
			if (ch != ' ' && ch != '\n' && sh<this->count)
			{
				if (temp == 0)
					this->coordinate[sh].x = int(ch) - 48;
				if (temp == 1)
					this->coordinate[sh].y = int(ch) - 48;
				temp++;
				if (temp == 2)
				{
					sh++;
					temp = 0;
				}
			}
		}

}// что такое sh, ch и temp?

void Cities::getWeight()
{
	weight.resize( this->count , std::vector<int>(this->count) ); 
	std::vector<Coordinate>::iterator iter1;
	std::vector<Coordinate>::iterator iter2;
	iter1 = coordinate.begin();
	iter2 = coordinate.begin()+1;
	
	for (int i = 0; i < this->count; i++) 
	{
		for (int j = i; j < this->count ; j++) 
		{
			if (j == i)
			{
				weight[i][j] = sqrt(std::pow((iter2->x - iter1->x), 2) + std::pow((iter2->y - iter1->y), 2));

				continue;
			}
			

			weight[i][j] = sqrt(std::pow((iter2->x - iter1->x), 2) + std::pow((iter2->y - iter1->y), 2));
			++iter1;
			++iter2;
		}
			iter1 = coordinate.begin();
	iter2 = coordinate.begin()+1;
	}
};


void Cities::InitializationPoints(std::string path, int argc, char* argv[])
{

	std::ifstream in((argc > 1) ? argv[1] : path);
	std::istream_iterator<Point> begin(in);
	std::istream_iterator<Point> end;
	
	Triangulation t;
	t.insert(begin, end);
	
	this->TBeforeCarving = t;
	this->TAfterCarving = t;



	getCoordinate(path);
	getWeight();

}


void Cities::DrawBeforeCarving()
{
	draw(this->TBeforeCarving);

}

void Cities::DrawAfterCarving()
{
	draw(this->TAfterCarving);

}

Carving::Carving()
{

}

Carving::~Carving()
{

}

void Carving::MergeFaces(Cities& cities)
{
	int i = 0;
	bool check = true;
	Triangulation::Finite_faces_iterator it;
	for (it = cities.TAfterCarving.finite_faces_begin(); it != cities.TAfterCarving.finite_faces_end(); it++)
	{
		
		for (int j = 0; j < cities.count / 3; j++)
			if (i == traping[j].groups)
				check = false;
			if(check)
			cities.TAfterCarving.delete_face(it);
			check = true;
		
		i++;

	}
}

void Carving::Generate_path(Cities& cities, int begin_trap, int end_trap)
{
	begin_trap;
	end_trap;
	int variants_path=cities.count/3;
    
	Triangulation::Finite_vertices_iterator it;
	Triangulation::Finite_vertices_iterator it2;
	for (it = cities.TBeforeCarving.finite_vertices_begin(), it2 = ++cities.TBeforeCarving.finite_vertices_begin(); it2 != --cities.TBeforeCarving.finite_vertices_end(); it++, it2++)
		it->set_associated_vertex(it2);

	Triangulation::Finite_vertices_iterator it3;
	for (it3 = cities.TBeforeCarving.finite_vertices_begin(); it3 != cities.TBeforeCarving.finite_vertices_end(); it3++)
		cities.Vertex.push_back(it3);

	this->traping.resize(cities.count);
	
	this->traping[0].distance = 0;
	int b = 3, c = 0;
	int temp = 99999;
	for (int i = 0; i < variants_path - 1; i++)
	{
		
		for (int j = c; j < b; j++)

		{
			if (temp > cities.weight[i][j])
				temp = cities.weight[i][j];
			
		
			if (j == b-1)
			{
				
				this->traping[i].distance += temp;
				this->traping[i].groups=j;
			}
		}
		b += 3;
		c += 3;
	}
	/*std::system("pdflatex refman.tex");*/
}
