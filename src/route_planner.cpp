#include "route_planner.h"
#include <algorithm>


RoutePlanner::RoutePlanner
(
	RouteModel& model, 
	float start_x, 
	float start_y, 
	float end_x, 
	float end_y
): 
m_Model(model) 
{
	// Convert inputs to percentage:
	start_x *= 0.01;
	start_y *= 0.01;
	end_x *= 0.01;
	end_y *= 0.01;

	start_node = &m_Model.FindClosestNode(start_x, start_y);
	end_node = &m_Model.FindClosestNode(end_x, end_y);
}


float RoutePlanner::CalculateHValue(RouteModel::Node const *node) 
{
    return node->distance(*end_node);
}


void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) 
{
    current_node->FindNeighbors();

    for (auto neighbor_node: current_node->neighbors) 
	{
        neighbor_node->parent = current_node;
        neighbor_node->h_value = CalculateHValue(neighbor_node);
        neighbor_node->g_value = 
			(current_node->g_value) + (current_node->distance(*neighbor_node));
        neighbor_node->visited = true; 
        open_list.push_back(neighbor_node);
    }
}


RouteModel::Node *RoutePlanner::NextNode() {
    sort
	(
		open_list.begin(), 
		open_list.end(), 
		[](const RouteModel::Node* a, const RouteModel::Node* b) 
		{
			return (a->g_value + a->h_value) > (b->g_value + b->h_value);
		}
    );

    auto next_node = open_list.back();
    open_list.pop_back();

    return next_node;
}


std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath
(
	RouteModel::Node *current_node
) 
{
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    RouteModel::Node* child_node = current_node;
    RouteModel::Node* parent_node = current_node->parent;

    bool start_reached = false;

    while(start_reached == false) 
	{
        path_found.push_back(*child_node);
        distance = distance + child_node->distance(*parent_node);
        if (parent_node == start_node) 
		{
            path_found.push_back(*parent_node);
            start_reached = true;
        } 
		else 
		{
            child_node = parent_node;
            parent_node = child_node->parent;
        }
    }

    std::reverse(path_found.begin(), path_found.end());

    // Multiply the distance by the scale of the map to get meters.
	distance *= m_Model.MetricScale(); 
    return path_found;
}


void RoutePlanner::AStarSearch() 
{
    RouteModel::Node *current_node = nullptr;
    start_node->visited = true;
    open_list.emplace_back(start_node);
    current_node = start_node;

    while (current_node != end_node) 
	{
        AddNeighbors(current_node);
        current_node = NextNode();
    }

    m_Model.path = ConstructFinalPath(current_node);
}