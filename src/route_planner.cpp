#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    this->start_node = &m_Model.FindClosestNode(start_x, start_y);
    this->end_node = &m_Model.FindClosestNode(end_x, end_y);
}

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return node->distance(*(this->end_node));
}

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {

    current_node->FindNeighbors();

    for (RouteModel::Node* node: current_node->neighbors) {
        node->parent = current_node;
        node->h_value = CalculateHValue(node);
        node->g_value = (current_node->g_value) + (current_node->distance(*node));
        (this->open_list).push_back(node);
        node->visited = true; 
    }

}

bool Node_Compare(const RouteModel::Node* node1, const RouteModel::Node* node2){
    float f1 = node1->g_value + node1->h_value;
    float f2 = node2->g_value + node2->h_value;
    return f1 > f2;
}

RouteModel::Node *RoutePlanner::NextNode() {
    // Reminder: sort() arranges from lower to higher by default. 
    sort(open_list.begin(), open_list.end(), Node_Compare);
    auto next_node = (this->open_list).back();
    (this->open_list).pop_back();
    return next_node;
}

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    RouteModel::Node* child_node = current_node;
    RouteModel::Node* parent_node = current_node->parent;

    bool start_reached = false;

    while(start_reached == false) {
        path_found.insert(path_found.begin(), *child_node);
        distance = distance + child_node->distance(*parent_node);
        if (parent_node == start_node) {
            path_found.insert(path_found.begin(), *parent_node);
            start_reached = true;
        } else {
            child_node = parent_node;
            parent_node = child_node->parent;
        }
    }

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;
}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here.

}