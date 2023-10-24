#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/draw_triangulation_2.h>
#include <CGAL/boost/graph/Euler_operations.h>
#include <CGAL/Vector_2.h>
#include <cassert>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>

#ifndef APPLE_CARVING_HPP
#define APPLE_CARVING_HPP
/// @file AppleCarving.hpp*
/// @brief Предоставляет классы и методы реализации алгоритма Apple Carving.

/// @class My_vertex_base*.2
/// @brief Класс, реализующий построение триангуляции
template <class Gt, class Vb = CGAL::Triangulation_vertex_base_2<Gt>>
class My_vertex_base
	: public Vb
{
	///@brief Переопределенный тип Vb
	typedef Vb Base;
public:
	///@brief Переопределенный тип Vertex_handle
	typedef typename Vb::Vertex_handle Vertex_handle;

	///@brief Переопределенный тип Face_handle
	typedef typename Vb::Face_handle Face_handle;

	///@brief Переопределенный тип Point
	typedef typename Vb::Point Point;

	template < typename TDS2 >
	struct Rebind_TDS {
		typedef typename Vb::template Rebind_TDS<TDS2>::Other Vb2;
		typedef My_vertex_base<Gt, Vb2> Other;
	};

private:
	Vertex_handle  va_;

public:
	///@brief Конструктор класса 1
	My_vertex_base() : Base() {}
	///@brief Конструктор класса 2
	My_vertex_base(const Point& p) : Base(p) {}
	///@brief Конструктор класса 3
	My_vertex_base(const Point& p, Face_handle f) : Base(f, p) {}
	///@brief Конструктор класса 4
	My_vertex_base(Face_handle f) : Base(f) {}

	///@brief Устанавливает связи между вершинами
	void set_associated_vertex(Vertex_handle va) { va_ = va; }
	Vertex_handle get_associated_vertex() { return va_; }
};

///@brief Переопределенный тип K
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

///@brief Переопределенный тип Vb
typedef My_vertex_base<K> Vb;

///@brief Переопределенный тип Tds
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;

///@brief Переопределенный тип Triangulation
typedef CGAL::Triangulation_2<K, Tds> Triangulation;

///@brief Переопределенный тип Vertex_handle
typedef Triangulation::Vertex_handle Vertex_handle;

///@brief Переопределенный тип Finite_faces_iterator
typedef Triangulation::Finite_faces_iterator Finite_faces_iterator;

///@brief Переопределенный тип Point
typedef Triangulation::Point Point;

///@brief Структура координат точек триангуляции
struct Coordinate
{
	///@brief Координата x
	int x;

	///@brief Координата y
	int y;
};
///@brief Структура содержащая оптимальный путь
struct Traping
{
	///@brief Точки оптимального пути
	int groups;

	///@brief Расстояние оптимального пути
	int distance;
	
};

/// @class Cities*
/// @brief Класс, содержащий информацию о городах.
class Cities
{
public:
	///@brief  Количество городов
	int count;

	///@brief  Путь к файлу
	std::string path;

	///@brief  Координаты точек триангуляции
	std::vector <Coordinate> coordinate;

	///@brief  Расстояния между городами
	std::vector <std::vector <int>> weight;

	///@brief  Триангуляция до применения алгоритма
	Triangulation TBeforeCarving;

	///@brief  Триангуляция после применения алгоритма
	Triangulation TAfterCarving;

	///@brief  Вершины триангуляции
	std::vector <Vertex_handle> Vertex;

	///@brief Конструктор класса
	Cities();

	///@brief Деструктор класса
	~Cities();

	/// @brief Установка количества городов
	void getCount(std::string path);

	///@brief Получение координат.
	void getCoordinate(std::string path);

	/// @brief Установка расстояния между городами.
	void getWeight();

	/// @brief Инициализация расстояний между городами
	void InitializationPoints(std::string path, int argc, char* argv[]);

	/// @brief Отрисовывает триангуляцию перед применением алгоритма Apple Carving
	void DrawBeforeCarving();

	/// @brief Отрисовывает триангуляцию после применения алгоритма Apple Carving
	void DrawAfterCarving();

};

/// @class Carving*
/// @brief Класс, реализающий алгоритм AppleCarving.
class Carving {

public:
	///@brief  Вектор содержащий все варианты путей
	std::vector<Traping> traping;

	///@brief Конструктор класса
	Carving();

	///@brief Деструктор класса
	~Carving();

	/// @brief Вырезает полигоны из триангуляции
	void MergeFaces(Cities& cities);

	/// @brief Поиск оптимального пути
	void Generate_path(Cities& cities, int begin_trap, int end_trap);

};
#endif