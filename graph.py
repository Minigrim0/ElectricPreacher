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
        G.add_nodes_from(self.nodes)
        G.add_edges_from(self.edges)
        nx.draw_networkx(G)
        plt.show()


class Node:
    def __init__(self, name):
        self.name = str(name)

    def __str__(self):
        return self.name

    def __repr__(self):
        return self.__str__()


def build_graph(pathlist, graph):
    for index, path in enumerate(pathlist):
        if "vendor" in str(path):
            continue
        reg = re.compile(r'#include\s*<(.*)>')
        reg2 = re.compile(r'#include\s*"(.*)"')

        root_node = Node(str(path).replace("MiniEngine/src/", ""))
        if not graph.exists(root_node):
            print(f"{index} Root Node {root_node} does not exist yet")
            graph.add_node(root_node)

        pragma_found = False
        with open(path, 'r') as file:
            for line in file:
                if "#pragma once" in line:
                    pragma_found = True
                    continue

                match = reg.match(line)
                match2 = reg2.match(line)
                if match:
                    node_name = match.group(1)
                elif match2:
                    node_name = match2.group(1)
                else:
                    continue

                # print(f"{index} Found {node_name} in {path}")
                if not graph.exists(node_name):
                    # print(f"{index} Node {node_name} does not exist yet")
                    graph.add_node(Node(node_name))
                # print(f"{index} Adding edge from {root_node} to {node_name}")
                graph.add_edge(root_node, graph.get(node_name))
        if ".hpp" in str(path) and not pragma_found:
            print(f"{index} No #pragma once found in {path}")


graph = Graph()
build_graph(Path("./MiniEngine/src/").rglob('*.hpp'), graph)
build_graph(Path("./MiniEngine/src/").rglob('*.cpp'), graph)

for node in sorted(graph.nodes, key=lambda x: x.name):
    print(node)

print(graph)
graph.visualize()
