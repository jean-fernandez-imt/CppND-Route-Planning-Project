#include <optional>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <io2d.h>
#include "route_model.h"
#include "render.h"
#include "route_planner.h"

using namespace std::experimental;

static std::optional<std::vector<std::byte>> ReadFile(const std::string &path)
{   
    std::ifstream is{path, std::ios::binary | std::ios::ate};
    if( !is )
        return std::nullopt;
    
    auto size = is.tellg();
    std::vector<std::byte> contents(size);    
    
    is.seekg(0);
    is.read((char*)contents.data(), size);

    if( contents.empty() )
        return std::nullopt;
    return std::move(contents);
}


bool CheckRange(int user_input, int min_val, int max_val) 
{
    if (user_input >= min_val && user_input <= max_val) 
    {
        return true;
    } 
    else 
    {
        return false;
    }
}


int GetInput() 
{
    int user_input;
    std::cout << "Enter value: ";
    std::cin >> user_input;

    while (CheckRange(user_input, 0, 100) == false) {
        std::cout << "Value not in [0, 100] range. Try again!" << std::endl;
        std::cout << "Enter value: ";
        std::cin >> user_input;
    }

    return user_input;
}


int main(int argc, const char **argv)
{    
    std::string osm_data_file = "";
    if( argc > 1 ) 
    {
        for( int i = 1; i < argc; ++i )
            if( std::string_view{argv[i]} == "-f" && ++i < argc )
                osm_data_file = argv[i];
    }
    else 
    {
        std::cout << "To specify a map file use the following format: " << std::endl;
        std::cout << "Usage: [executable] [-f filename.osm]" << std::endl;
        osm_data_file = "../map.osm";
    }
    
    std::vector<std::byte> osm_data;
 
    if( osm_data.empty() && !osm_data_file.empty() ) 
    {
        std::cout << "Reading OpenStreetMap data from the following file: " <<  osm_data_file << std::endl;
        auto data = ReadFile(osm_data_file);
        if( !data )
            std::cout << "Failed to read." << std::endl;
        else
            osm_data = std::move(*data);
    }
    
    float start_x, start_y, end_x, end_y;

    std::cout << "Start X coordinate: " << std::endl;
    start_x = GetInput();
    std::cout << "Start Y coordinate: " << std::endl;
    start_y = GetInput();
    std::cout << "Target X coordinate: " << std::endl;
    end_x = GetInput();
    std::cout << "Target Y coordinate: " << std::endl;
    end_y = GetInput();

    // Build Model.
    RouteModel model{osm_data};

    // Create RoutePlanner object and perform A* search.
    RoutePlanner route_planner{model, start_x, start_y, end_x, end_y};
    route_planner.AStarSearch();

    std::cout << "Distance: " << route_planner.GetDistance() << " meters. \n";

    // Render results of search.
    Render render{model};

    auto display = io2d::output_surface{400, 400, io2d::format::argb32, io2d::scaling::none, io2d::refresh_style::fixed, 30};
    display.size_change_callback([](io2d::output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](io2d::output_surface& surface){
        render.Display(surface);
    });
    display.begin_show();
}
