#include "operation.h"
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <stdio.h>

int main_gradient(void)
{
    Agraph_t *g;
    Agnode_t *n, *m, *o, *p;
    Agedge_t *e, *e2, *e3;
    GVC_t *gvc;

    // Create a new graph
    g = agopen("g", Agdirected, NULL);
    agsafeset(g, "rankdir", "LR", "");

    // Create nodes with record shapes
    n = agnode(g, "n", 1);
    m = agnode(g, "m", 1);
    o = agnode(g, "o", 1);
    p = agnode(g, "p", 1);

    // Set the record label for each node
    agsafeset(n, "shape", "record", "");
    agsafeset(n, "label", "{x2 | data 0.0000 | grad 0.0000}", "");

    agsafeset(m, "shape", "record", "");
    agsafeset(m, "label", "{w2 | data 1.0000 | grad 0.0000}", "");

    agsafeset(o, "shape", "record", "");
    agsafeset(o, "label", "{<f0> x2*w2 | data 0.0000 | grad 0.5000}", "");

    agsafeset(p, "shape", "record", "");
    agsafeset(p, "label", "{<f0> x1*w1 | data -6.0000 | grad 0.5000}", "");

    // Create edges between the nodes
    e = agedge(g, n, o, 0, 1);
    e2 = agedge(g, m, o, 0, 1);
    e3 = agedge(g, o, p, 0, 1);

    // Set labels for edges
    agsafeset(e, "label", "*", "");
    agsafeset(e2, "label", "*", "");
    agsafeset(e3, "label", "+", "");

    // Create a Graphviz context
    gvc = gvContext();

    // Set the layout engine
    gvLayout(gvc, g, "dot");

    // Render the graph to SVG
    gvRenderFilename(gvc, g, "svg", "graph.svg");

    // Free layout resources
    gvFreeLayout(gvc, g);

    // Free Graphviz context
    gvFreeContext(gvc);

    // Close the graph
    agclose(g);

    return 0;
}
