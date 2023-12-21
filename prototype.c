#include "operation.h"
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <stdio.h>

int main_gradient(void)
{
    Agraph_t *g;
    Agnode_t *n, *m;
    Agedge_t *e;
    GVC_t *gvc;

    // Create a new graph
    g = agopen("g", Agdirected, NULL);

    // Add nodes and an edge
    n = agnode(g, "n", 1);
    m = agnode(g, "m", 1);
    e = agedge(g, n, m, NULL, 1);

    // Set some attributes using agsafeset
    agsafeset(n, "color", "red", "");
    agsafeset(e, "label", "Edge from n to m", "");

    // Create a Graphviz context
    gvc = gvContext();

    // Set the layout engine (e.g., dot, neato)
    gvLayout(gvc, g, "dot");

    // Render the graph to SVG
    gvRenderFilename(gvc, g, "svg", "graph.svg");

    // Free layout resources
    gvFreeLayout(gvc, g);

    // Free other resources
    gvFreeContext(gvc);
    agclose(g);

    return 0;
}
