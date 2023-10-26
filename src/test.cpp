//
//  test.cpp
//
//  Tests to prove your code works.
//  You should NOT modify this file.
//
//  Copyright 2019 David Kopec
//
//  Permission is hereby granted, free of charge, to any person
//  obtaining a copy of this software and associated documentation files
//  (the "Software"), to deal in the Software without restriction,
//  including without limitation the rights to use, copy, modify, merge,
//  publish, distribute, sublicense, and/or sell copies of the Software,
//  and to permit persons to whom the Software is furnished to do so,
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice
//  shall be included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  OTHER DEALINGS IN THE SOFTWARE.

#include "Graph.h"
#include "catch.h"
#include <string>
#include <list>
#include <iostream>

using namespace std;
using namespace csi281;

template<typename T>
void printPath(list<T> &l) {
    for (auto &x : l) {
        if (x != l.back()) {
            cout << x << " -> ";
        } else {
            cout << x;
        }
    }
    cout << endl;
}

TEST_CASE( "edgeExists() Tests", "[graph]" ) {
    SECTION( "Graph w/ int tests" ) {
        Graph<int> g1 = Graph<int>();
        for (int i = 0; i < 10; i++) {
            g1.addEdge(i, i + 1);
        }
        cout << "------g1------" << endl;
        g1.debugPrint();
        CHECK( g1.edgeExists(0, 1) );
        CHECK( g1.edgeExists(5, 4) );
        CHECK( g1.edgeExists(9, 10) );
        CHECK( !g1.edgeExists(4, 6) );
        CHECK( !g1.edgeExists(2, 20) );
        CHECK( !g1.edgeExists(20, 2) );
    }
    
    SECTION( "Graph w/ string tests" ) {
        Graph<string> cityGraph = Graph<string>();
        cityGraph.addEdge("Seattle", "Chicago");
        cityGraph.addEdge("Seattle", "Denver");
        cityGraph.addEdge("Seattle", "San Francisco");
        cityGraph.addEdge("San Francisco", "Denver");
        cityGraph.addEdge("San Francisco", "Los Angeles");
        cityGraph.addEdge("Los Angeles", "Denver");
        cityGraph.addEdge("Los Angeles", "Kansas City");
        cityGraph.addEdge("Los Angeles", "Dallas");
        cityGraph.addEdge("Denver", "Chicago");
        cityGraph.addEdge("Denver", "Kansas City");
        cityGraph.addEdge("Kansas City", "Chicago");
        cityGraph.addEdge("Kansas City", "New York");
        cityGraph.addEdge("Kansas City", "Atlanta");
        cityGraph.addEdge("Kansas City", "Dallas");
        cityGraph.addEdge("Chicago", "Boston");
        cityGraph.addEdge("Chicago", "New York");
        cityGraph.addEdge("Boston", "New York");
        cityGraph.addEdge("Atlanta", "New York");
        cityGraph.addEdge("Atlanta", "Dallas");
        cityGraph.addEdge("Atlanta", "Houston");
        cityGraph.addEdge("Atlanta", "Miami");
        cityGraph.addEdge("Houston", "Miami");
        cityGraph.addEdge("Houston", "Dallas");
        cout << "------cityGraph------" << endl;
        cityGraph.debugPrint();
        CHECK( cityGraph.edgeExists("Seattle", "Denver") );
        CHECK( cityGraph.edgeExists("Houston", "Dallas") );
        CHECK( cityGraph.edgeExists("Miami", "Atlanta") );
        CHECK( !cityGraph.edgeExists("Denver", "Dallas") );
        CHECK( !cityGraph.edgeExists("Denver", "Burlington") );
        CHECK( !cityGraph.edgeExists("Burlington", "New York") );
    }
}

TEST_CASE( "dfs() Tests", "[graph]" ) {
    SECTION( "Graph w/ int tests" ) {
        Graph<int> g1 = Graph<int>();
        for (int i = 0; i < 10; i++) {
            g1.addEdge(i, i + 1);
        }
        auto pathopt = g1.dfs(0, 10);
        CHECK( pathopt.has_value() );
        auto path = pathopt.value();
        cout << "------dfs g1 path------" << endl;
        printPath(path);
        CHECK( path.size() == 11 );
        CHECK( path.front() == 0 );
        CHECK( path.back() == 10 );
        auto it = path.begin();
        auto last = path.front();
        for (unsigned long i = 1; i < path.size(); i++) {
            it++;
            auto current = *it;
            CHECK (g1.edgeExists(last, current));
            last = current;
        }
    }
    
    SECTION( "Graph w/ string tests" ) {
        Graph<string> cityGraph = Graph<string>();
        cityGraph.addEdge("Seattle", "Chicago");
        cityGraph.addEdge("Seattle", "Denver");
        cityGraph.addEdge("Seattle", "San Francisco");
        cityGraph.addEdge("San Francisco", "Denver");
        cityGraph.addEdge("San Francisco", "Los Angeles");
        cityGraph.addEdge("Los Angeles", "Denver");
        cityGraph.addEdge("Los Angeles", "Kansas City");
        cityGraph.addEdge("Los Angeles", "Dallas");
        cityGraph.addEdge("Denver", "Chicago");
        cityGraph.addEdge("Denver", "Kansas City");
        cityGraph.addEdge("Kansas City", "Chicago");
        cityGraph.addEdge("Kansas City", "New York");
        cityGraph.addEdge("Kansas City", "Atlanta");
        cityGraph.addEdge("Kansas City", "Dallas");
        cityGraph.addEdge("Chicago", "Boston");
        cityGraph.addEdge("Chicago", "New York");
        cityGraph.addEdge("Boston", "New York");
        cityGraph.addEdge("Atlanta", "New York");
        cityGraph.addEdge("Atlanta", "Dallas");
        cityGraph.addEdge("Atlanta", "Houston");
        cityGraph.addEdge("Atlanta", "Miami");
        cityGraph.addEdge("Houston", "Miami");
        cityGraph.addEdge("Houston", "Dallas");
        // Expect a valid path from Seattle to Miami
        auto pathopt = cityGraph.dfs("Seattle", "Miami");
        CHECK( pathopt.has_value() );
        auto path = pathopt.value();
        cout << "------dfs cityGraph path------" << endl;
        printPath(path);
        CHECK( path.front() == "Seattle" );
        CHECK( path.back() == "Miami" );
        auto it = path.begin();
        auto last = path.front();
        for (unsigned long i = 1; i < path.size(); i++) {
            it++;
            auto current = *it;
            CHECK (cityGraph.edgeExists(last, current));
            last = current;
        }
    }
}

TEST_CASE( "bfs() Tests", "[graph]" ) {
    SECTION( "Graph w/ int tests" ) {
        Graph<int> g1 = Graph<int>();
        for (int i = 0; i < 10; i++) {
            g1.addEdge(i, i + 1);
        }
        auto pathopt = g1.bfs(0, 10);
        CHECK( pathopt.has_value() );
        auto path = pathopt.value();
        cout << "------bfs g1 path------" << endl;
        printPath(path);
        CHECK( path.size() == 11 );
        CHECK( path.front() == 0 );
        CHECK( path.back() == 10 );
        auto it = path.begin();
        auto last = path.front();
        for (unsigned long i = 1; i < path.size(); i++) {
            it++;
            auto current = *it;
            CHECK (g1.edgeExists(last, current));
            last = current;
        }
    }
    
    SECTION( "Graph w/ string tests" ) {
        Graph<string> cityGraph = Graph<string>();
        cityGraph.addEdge("Seattle", "Chicago");
        cityGraph.addEdge("Seattle", "Denver");
        cityGraph.addEdge("Seattle", "San Francisco");
        cityGraph.addEdge("San Francisco", "Denver");
        cityGraph.addEdge("San Francisco", "Los Angeles");
        cityGraph.addEdge("Los Angeles", "Denver");
        cityGraph.addEdge("Los Angeles", "Kansas City");
        cityGraph.addEdge("Los Angeles", "Dallas");
        cityGraph.addEdge("Denver", "Chicago");
        cityGraph.addEdge("Denver", "Kansas City");
        cityGraph.addEdge("Kansas City", "Chicago");
        cityGraph.addEdge("Kansas City", "New York");
        cityGraph.addEdge("Kansas City", "Atlanta");
        cityGraph.addEdge("Kansas City", "Dallas");
        cityGraph.addEdge("Chicago", "Boston");
        cityGraph.addEdge("Chicago", "New York");
        cityGraph.addEdge("Boston", "New York");
        cityGraph.addEdge("Atlanta", "New York");
        cityGraph.addEdge("Atlanta", "Dallas");
        cityGraph.addEdge("Atlanta", "Houston");
        cityGraph.addEdge("Atlanta", "Miami");
        cityGraph.addEdge("Houston", "Miami");
        cityGraph.addEdge("Houston", "Dallas");
        // Expect a valid path from Seattle to Miami of length 5
        auto pathopt = cityGraph.bfs("Seattle", "Miami");
        CHECK( pathopt.has_value() );
        auto path = pathopt.value();
        cout << "------bfs cityGraph path------" << endl;
        printPath(path);
        CHECK( path.front() == "Seattle" );
        CHECK( path.back() == "Miami" );
        CHECK( path.size() == 5 );
        auto it = path.begin();
        auto last = path.front();
        for (unsigned long i = 1; i < path.size(); i++) {
            it++;
            auto current = *it;
            CHECK (cityGraph.edgeExists(last, current));
            last = current;
        }
    }
}
