#include "route_planner.h"
#include <algorithm>
#include <fstream>
#include <iomanip>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.
    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);
}


// Implement the CalculateHValue method.
float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return node->distance(*end_node);
}


// AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->FindNeighbors();

    for (auto neighbor : current_node->neighbors) {
        if (!neighbor->visited) {
            neighbor->parent = current_node;
            neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
            neighbor->h_value = CalculateHValue(neighbor);
            open_list.push_back(neighbor);
            neighbor->visited = true;
        }
    }

}


// NextNode method to sort the open list and return the next node.
RouteModel::Node *RoutePlanner::NextNode() {
    std::sort(open_list.begin(), open_list.end(),
                [](const auto *a, const auto *b){
                    return (a->g_value + a->h_value) > (b->g_value + b->h_value);
                });
    RouteModel::Node *lowest = open_list.back();
    open_list.pop_back();
    return lowest;
}


// ConstructFinalPath method to return the final path found from your A* search.
std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    while (current_node->parent != nullptr){
        path_found.push_back(*current_node);
        distance += current_node->distance(*current_node->parent);
        current_node = current_node->parent;
    }

    path_found.push_back(*current_node); // add start_node

    std::reverse(path_found.begin(), path_found.end());
    
    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}

// ExportGeoJSON method to export the final path as a GeoJSON file.
void RoutePlanner::ExportGeoJSON(const std::vector<RouteModel::Node>& path) {
    std::ofstream file("route.geojson");

    if (!file.is_open()) {
        std::cerr << "Failed to create GeoJSON file.\n";
        return;
    }

    file << std::fixed << std::setprecision(6);

    file << "{\n";
    file << R"(  "type": "FeatureCollection",)" << "\n";
    file << R"(  "features": [)" << "\n";
    file << "    {\n";
    file << R"(      "type": "Feature",)" << "\n";
    file << R"(      "geometry": {)" << "\n";
    file << R"(        "type": "LineString",)" << "\n";
    file << R"(        "coordinates": [)" << "\n";

    for (size_t i = 0; i < path.size(); ++i) {
        file << "          ["
             << path[i].x << ", "
             << path[i].y << "]";

        if (i < path.size() - 1)
            file << ",";

        file << "\n";
    }

    file << "        ]\n";
    file << "      },\n";

    file << R"(      "properties": {)" << "\n";
    file << R"(        "distance_meters": )" << distance << "\n";
    file << "      }\n";

    file << "    }\n";
    file << "  ]\n";
    file << "}\n";

    file.close();

    std::cout << "GeoJSON exported: route.geojson\n";
}


// A* Search algorithm here.
void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    start_node->visited = true;
    open_list.push_back(start_node);

    while (!open_list.empty()) {
        current_node = NextNode();

        if (current_node == end_node) {
            m_Model.path = ConstructFinalPath(current_node);
            ExportGeoJSON(m_Model.path);
            return;
        }

        AddNeighbors(current_node);
    }

}