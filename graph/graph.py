import re
from pathlib import Path as pathlibPath

import redis
import redisgraph


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

    def to_redis(self, redis_graph):
        for node in self.nodes:
            redis_graph.add_node(node.node)
        for edge in self.edges:
            redis_graph.add_edge(
                redisgraph.Edge(edge[0].node, "includes", edge[1].node)
            )
        redis_graph.commit()

    def __str__(self):
        return "Graph with {} nodes and {} edges".format(len(self.nodes), len(self.edges))


class Node:
    def __init__(self, name):
        self.name = str(name)
        self.node = redisgraph.Node(
            label='file',
            properties={'name': self.name}
        )

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


r = redis.Redis(host='localhost', port=6379, db=0)
redis_graph = redisgraph.Graph('imports', r)
graph = Graph()
build_graph(pathlibPath("./MiniEngine/src/").rglob('*.hpp'), graph)
build_graph(pathlibPath("./MiniEngine/src/").rglob('*.cpp'), graph)

for node in sorted(graph.nodes, key=lambda x: x.name):
    print(node)

print(graph)
graph.to_redis(redis_graph)
