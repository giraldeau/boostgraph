#include <boost/graph/dag_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>

#include <iostream>

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    using namespace boost;
    using namespace std;

    typedef adjacency_list<vecS, vecS, directedS,
            property<vertex_distance_t, int>,
            property<edge_weight_t, int> > graph_t;

    graph_t graph(6);
    enum verts { a, b, c , d, e, f, g, h, i, j };
    char name[] = "abcdefghij";
    add_edge(a, b, 1, graph);
    add_edge(b, c, 1, graph);
    add_edge(c, d, 0, graph);
    add_edge(d, e, 1, graph);

    add_edge(f, g, 2, graph);

    add_edge(b, f, 0, graph);
    add_edge(g, d, 0, graph);

    property_map<graph_t, vertex_distance_t>::type
        d_map = get(vertex_distance, graph);

    dag_shortest_paths(graph, a,
                       distance_map(d_map)
                        .distance_compare(std::greater<int>())
                        .distance_inf((std::numeric_limits<int>::min)())
                        .distance_zero(0));

    graph_traits<graph_t>::vertex_iterator vi, vi_end;
    for(tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi) {
        if (d_map[*vi] == (numeric_limits<int>::max)()) {
            cout << name[*vi] << ":infinity\n";
        } else {
            cout << name[*vi] << ": " << d_map[*vi] << "\n";
        }
    }


    cout << "vertices(g) = {";
    typedef typename graph_traits<graph_t>::vertex_iterator iter_t;
    for (pair<iter_t, iter_t> p = vertices(graph); p.first != p.second; ++p.first) {
        cout << *p.first << " ";
    }
    cout << "}" << endl;

    // Problem with tie() (expected primamary-expression, looks like a syntax error)
    /*
    cout << "edges(g) = {";
    typedef typename graph_traits<graph_t>::edge_iterator one, two;
    for (tie(one, two) = edges(g); one != two; ++one) {
        //cout << *first << " ";
    }
    cout << "}" << endl;
    */

    return 0;
}
