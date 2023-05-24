import re
from pathlib import Path

import networkx as nx
import matplotlib.pyplot as plt

class Graph:
    def __init__(self):
        self.nodes = []
        self.edges = []

    def add_node(self, node):
        self.nodes.append(node)

    def add_edge(self, Node1, Node2):
        self.edges.append((Node1, Node2))

    def exists(self, node_name):
        for node in self.nodes:
            if node.name == node_name:
                return True
        return False
    
    def get(self, node_name):
        for node in self.nodes:
            if node.name == node_name:
                return node
        return None

    def __str__(self):
        return "Graph with {} nodes and {} edges".format(len(self.nodes), len(self.edges))

    def visualize(self):
        G = nx.Graph()
        G.add_edges_from(self.edges)
        nx.draw_networkx(G)
        plt.show()


class Node:
    def __init__(self, name):
        self.name = name

    def __str__(self):
        return self.name

    def __repr__(self):
        return self.__str__()

def build_graph(pathlist, graph):
    for path in pathlist:
        if "vendor" in str(path):
            continue
        reg = re.compile(r'#include\s*<(.*)>')

        root_node = Node(path.name)
        with open(path, 'r') as file:
            for line in file:
                match = reg.match(line)
                if match:
                    node_name = match.group(1)
                    if not graph.exists(node_name):
                        graph.add_node(Node(node_name))
                    graph.add_edge(root_node, graph.get(node_name))


graph = Graph()
build_graph(Path("./MiniEngine").rglob('*.hpp'), graph)
build_graph(Path("./MiniEngine").rglob('*.cpp'), graph)


print(graph)
graph.visualize()
