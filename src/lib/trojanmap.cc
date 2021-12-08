#include "trojanmap.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <fstream>
#include <locale>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
// #include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <cctype>
#include <unordered_set>
#include <stack>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

//-----------------------------------------------------
// TODO (Students): You do not and should not change the following functions:
//-----------------------------------------------------

/**
 * PrintMenu: Create the menu
 * 
 */
void TrojanMap::PrintMenu() {

  std::string menu =
      "**************************************************************\n"
      "* Select the function you want to execute.                    \n"
      "* 1. Autocomplete                                             \n"
      "* 2. Find the position                                        \n"
      "* 3. CalculateShortestPath                                    \n"
      "* 4. Travelling salesman problem                              \n"
      "* 5. Cycle Detection                                          \n"
      "* 6. Topological Sort                                         \n"
      "* 7. Find K Closest Points                                    \n"
      "* 8. Exit                                                     \n"
      "**************************************************************\n";
  std::cout << menu << std::endl;
  std::string input;
  getline(std::cin, input);
  char number = input[0];
  switch (number)
  {
  case '1':
  {
    menu =
        "**************************************************************\n"
        "* 1. Autocomplete                                             \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a partial location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = Autocomplete(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '2':
  {
    menu =
        "**************************************************************\n"
        "* 2. Find the position                                        \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = GetPosition(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.first != -1) {
      std::cout << "Latitude: " << results.first
                << " Longitude: " << results.second << std::endl;
      PlotPoint(results.first, results.second);
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '3':
  {
    menu =
        "**************************************************************\n"
        "* 3. CalculateShortestPath                                    \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the start location:";
    std::cout << menu;
    std::string input1;
    getline(std::cin, input1);
    menu = "Please input the destination:";
    std::cout << menu;
    std::string input2;
    getline(std::cin, input2);
    auto start = std::chrono::high_resolution_clock::now();
    //auto results = CalculateShortestPath_Dijkstra(input1, input2);
    auto results = CalculateShortestPath_Bellman_Ford(input1, input2);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
      std::cout << "The distance of the path is:" << CalculatePathLength(results) << " miles" << std::endl;
      PlotPath(results);
    } else {
      std::cout << "No route from the start point to the destination."
                << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '4':
  {
    menu =
        "**************************************************************\n"
        "* 4. Traveling salesman problem                              \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "In this task, we will select N random points on the map and you need to find the path to travel these points and back to the start point.";
    std::cout << menu << std::endl << std::endl;
    menu = "Please input the number of the places:";
    std::cout << menu;
    getline(std::cin, input);
    int num = std::stoi(input);
    std::vector<std::string> keys;
    for (auto x : data) {
      keys.push_back(x.first);
    }
    std::vector<std::string> locations;
    srand(time(NULL));
    for (int i = 0; i < num; i++)
      locations.push_back(keys[rand() % keys.size()]);
    PlotPoints(locations);
    std::cout << "Calculating ..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    // auto results = TravellingTrojan(locations);
    //auto results = TravellingTrojan_bruteforce(locations);
    //auto results = TravellingTrojan_2opt(locations);
    // auto results = TravellingTrojan_Genetic(locations);
    auto results = TravellingTrojan_3opt(locations);
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    CreateAnimation(results.second);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.second.size() != 0) {
      for (auto x : results.second[results.second.size()-1]) std::cout << x << std::endl;
      menu = "**************************************************************\n";
      std::cout << menu;
      std::cout << "The distance of the path is:" << results.first << " miles" << std::endl;
      PlotPath(results.second[results.second.size()-1]);
    } else {
      std::cout << "The size of the path is 0" << std::endl;
    }
    menu = "**************************************************************\n"
           "You could find your animation at src/lib/output.avi.          \n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '5':
  {
    menu =
        "**************************************************************\n"
        "* 5. Cycle Detection                                          \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the left bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    std::vector<double> square;
    square.push_back(atof(input.c_str()));

    menu = "Please input the right bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the upper bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the lower bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    auto start = std::chrono::high_resolution_clock::now();
    auto results = CycleDetection(square);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results == true)
      std::cout << "there exists cycle in the subgraph " << std::endl;
    else
      std::cout << "there exist no cycle in the subgraph " << std::endl;
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '6':
  {
    menu =
        "**************************************************************\n"
        "* 6. Topological Sort                                         \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the locations filename:";
    std::cout << menu;
    std::string locations_filename;
    getline(std::cin, locations_filename);
    menu = "Please input the dependencies filename:";
    std::cout << menu;
    std::string dependencies_filename;
    getline(std::cin, dependencies_filename);
    
    // Read location names from CSV file
    std::vector<std::string> location_names;
    if (locations_filename == "") 
      location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
    else
      location_names = ReadLocationsFromCSVFile(locations_filename);
    
    // Read dependencies from CSV file
    std::vector<std::vector<std::string>> dependencies;
    if (dependencies_filename == "")
      dependencies = {{"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean1"}};
    else
      dependencies = ReadDependenciesFromCSVFile(dependencies_filename);

    // std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
    // std::vector<std::vector<std::string>> dependencies = {{"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean1"}};
    auto start = std::chrono::high_resolution_clock::now();
    auto result = DeliveringTrojan(location_names, dependencies);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************";
    std::cout << menu << std::endl;
    std::cout << "Topological Sorting Results:" << std::endl;
    for (auto x : result) std::cout << x << std::endl;
    std::vector<std::string> node_ids;
    for (auto x: result) {
      std::string id = GetID(x);
      node_ids.push_back(id);
    }
    PlotPointsOrder(node_ids);
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
    case '7':
  {
    menu =
        "**************************************************************\n"
        "* 7. Find K Closest Points                                    \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    
    menu = "Please input the locations:";
    std::cout << menu;
    std::string origin;
    getline(std::cin, origin);
    menu = "Please input k:";
    std::cout << menu;
    getline(std::cin, input);
    int k = std::stoi(input);
    
    auto start = std::chrono::high_resolution_clock::now();
    auto result = FindKClosestPoints(origin, k);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************";
    std::cout << menu << std::endl;
    std::cout << "Find K Closest Points Results:" << std::endl;
    int cnt = 1;
    for (auto x : result) { 
      std::cout << cnt << " " << data[x].name << std::endl;
      cnt++;
    }
    PlotPointsLabel(result, GetID(origin));
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '8':
    break;
  default:
  {
    std::cout << "Please select 1 - 8." << std::endl;
    PrintMenu();
    break;
  }
  }
}


/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * 
 */
void TrojanMap::CreateGraphFromCSVFile() {
  std::fstream fin;
  fin.open("src/lib/map.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '['), word.end());
      word.erase(std::remove(word.begin(), word.end(), ']'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}

/**
 * PlotPoint: Given a location id, plot the point on the map
 * 
 * @param  {std::string} id : location id
 */
void TrojanMap::PlotPoint(std::string id) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(data[id].lat, data[id].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}
/**
 * PlotPoint: Given a lat and a lon, plot the point on the map
 * 
 * @param  {double} lat : latitude
 * @param  {double} lon : longitude
 */
void TrojanMap::PlotPoint(double lat, double lon) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(lat, lon);
  cv::circle(img, cv::Point(int(result.first), int(result.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPath: Given a vector of location ids draws the path (connects the points)
 * 
 * @param  {std::vector<std::string>} location_ids : path
 */
void TrojanMap::PlotPath(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::line(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPoints(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points inside square
 * @param  {std::vector<double>} square : boundary
 */
void TrojanMap::PlotPointsandEdges(std::vector<std::string> &location_ids, std::vector<double> &square) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto upperleft = GetPlotLocation(square[2], square[0]);
  auto lowerright = GetPlotLocation(square[3], square[1]);
  cv::Point pt1(int(upperleft.first), int(upperleft.second));
  cv::Point pt2(int(lowerright.first), int(lowerright.second));
  cv::rectangle(img, pt2, pt1, cv::Scalar(0, 0, 255));
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    for(auto y : data[x].neighbors) {
      auto start = GetPlotLocation(data[x].lat, data[x].lon);
      auto end = GetPlotLocation(data[y].lat, data[y].lon);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPointsOrder: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPointsOrder(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::putText(img, data[x].name, cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
  }
  // Plot dots and lines
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::arrowedLine(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPointsLabel(std::vector<std::string> &location_ids, std::string origin) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  int cnt = 1;
  auto result = GetPlotLocation(data[origin].lat, data[origin].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 255, 0), cv::FILLED);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::putText(img, std::to_string(cnt), cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
    //cv::putText(img, GetName(x), cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
    cnt++;
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * CreateAnimation: Create the videos of the progress to get the path
 * 
 * @param  {std::vector<std::vector<std::string>>} path_progress : the progress to get the path
 */
void TrojanMap::CreateAnimation(std::vector<std::vector<std::string>> path_progress){
  cv::VideoWriter video("src/lib/output.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(1248,992));
  for(auto location_ids: path_progress) {
    std::string image_path = cv::samples::findFile("src/lib/input.jpg");
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
    cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
              cv::Scalar(0, 0, 255), cv::FILLED);
    for (auto i = 1; i < location_ids.size(); i++) {
      auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
      auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
      cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
                cv::Scalar(0, 0, 255), cv::FILLED);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
    video.write(img);
    cv::imshow("TrojanMap", img);
    cv::waitKey(1);
  }
	video.release();
}
/**
 * GetPlotLocation: Transform the location to the position on the map
 * 
 * @param  {double} lat         : latitude 
 * @param  {double} lon         : longitude
 * @return {std::pair<double, double>}  : position on the map
 */
std::pair<double, double> TrojanMap::GetPlotLocation(double lat, double lon) {
  std::pair<double, double> bottomLeft(34.01001, -118.30000);
  std::pair<double, double> upperRight(34.03302, -118.26502);
  double h = upperRight.first - bottomLeft.first;
  double w = upperRight.second - bottomLeft.second;
  std::pair<double, double> result((lon - bottomLeft.second) / w * 1248,
                                   (1 - (lat - bottomLeft.first) / h) * 992);
  return result;
}

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(std::string id) {
    Node n = data[id];
    return n.lat;
}


/**
 * GetLon: Get the longitude of a Node given its id. 
 * 
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(std::string id) { 
    Node n = data[id];
    return n.lon;
}

/**
 * GetName: Get the name of a Node given its id.
 * 
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(std::string id) { 
    Node n = data[id];
    return n.name;
}
 
/**
 * GetNeighborIDs: Get the neighbor ids of a Node.
 * 
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(std::string id) {
    Node n = data[id];
    return n.neighbors;
}

/**
 * CalculateDistance: Get the distance between 2 nodes. 
 * 
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id, const std::string &b_id) {
  // Do not change this function
  // TODO: Use Haversine Formula:
  // dlon = lon2 - lon1;
  // dlat = lat2 - lat1;
  // a = (sin(dlat / 2)) ^ 2 + cos(lat1) * cos(lat2) * (sin(dlon / 2)) ^ 2;
  // c = 2 * arcsin(min(1, sqrt(a)));
  // distances = 3961 * c;

  // where 3961 is the approximate radius of the earth at the latitude of
  // Washington, D.C., in miles
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2),2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2),2.0);
  double c = 2 * asin(std::min(1.0,sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0;i < path.size()-1; i++) {
    sum += CalculateDistance(path[i], path[i+1]);
  }
  return sum;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name){
  std::vector<std::string> results;
  int inputsize = name.size();
  std::string iname = name; // input name
  std::transform(iname.begin(), iname.end(), iname.begin(),[](unsigned char c){ return std::tolower(c); });
  
  for (auto i :data){
    Node n = i.second; // unordered_map<string, Node> data
    std::string nname = n.name; // name of the location(node)
    if (nname.size()==0){continue;}
    std::transform(nname.begin(), nname.end(), nname.begin(),[](unsigned char c){ return std::tolower(c); });
    
    //ta:7271 ch:6407
    int flag = 1;
    if (nname < iname) {flag = 0;}
    else{
      for (int i = 0;i<inputsize;i++){
        if (nname[i] == iname[i]) {continue;} 
        else{
          flag = 0;
          break;
        }
      }
    }
    if (flag == 1) {results.push_back(n.name);}
    
    /*
    //ta:6047 ch:6585
    if (nname.find(iname) == 0){
      results.push_back(n.name);
    }
    */
    
    /*
    //ta:6674 ch:7047
    if (nname.compare(0,inputsize,iname) ==0){
      results.push_back(n.name);
    }
    */
  }
  return results;
}

/**
 * GetPosition: Given a location name, return the position.
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  for(auto i:data){
    Node n = i.second;
    if(n.name == name){
      std::pair<double, double> results(n.lat, n.lon);
      return results;
    }
  }
  std::pair<double, double> results(-1, -1);
  return results;
 
}

/**
 * GetID: Given a location name, return the id. 
 * If the node does not exist, return an empty string. 
 *
 * @param  {std::string} name          : location name
 * @return {int}  : id
 */
std::string TrojanMap::GetID(std::string name) {
  for(auto i:data){
    Node n = i.second;
    if(n.name == name){
      return n.id;
    }
  }
  std::string res = "";
  return res;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
  // refer to "cpp tour - distance_matrix.cc"
  // O((m+n)logn). n-size of data, m-edges in the graph
  std::vector<std::string> path;
  std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>,
                      std::greater<std::pair<double, std::string>>> q; //use the priority queue
  std::string start, end; // the id of location1 and location2. source node and destination node
  std::unordered_map<std::string, double> distance; //distance map of the nodes
  std::unordered_map<std::string, std::string> pre; //record the node and its predecessor

  //initialize the distance map. o(n), n-length of data
  for (auto &i:data){
    distance[i.first] = INT_MAX;
    if (i.second.name == location1_name) {start = i.first;}
    if (i.second.name == location2_name) {end = i.first;}
  }

  distance[start] = 0; //the distance between start and start is 0
  q.push(std::make_pair(0, start)); //initialize the queue

  while (!q.empty()){ //n times
    std::string min_node = q.top().second;
    q.pop(); //delete the smallest node o(logn)

    if (min_node == end) {break;}

    //Relax distances 松弛算法
    std::vector<std::string> neigh = data[min_node].neighbors;
    for (auto &i:neigh){ //total (while & for) of o(2m)=o(m).
      double d = sqrt(pow(data[i].lat-data[min_node].lat,2)+pow(data[i].lon-data[min_node].lon,2));
      //double d = CalculateDistance(i, min_node);
      double new_dist = distance[min_node] + d;
      if (distance[i] > new_dist){
        distance[i] = new_dist;
        q.push(std::make_pair(distance[i], i)); //o(logn)
        //if the current min node can update node i's path, 
        //implying that current node is the predecessor of node i
        pre[i] = min_node; //update the predecessor of the node
      }
    }
  }
  if (pre.find(end) != pre.end()){
    std::string temp = end;
    while (temp != start){ //o(n)
      path.push_back(temp);
      temp = pre[temp];
      //std::cout << temp<<std::endl;
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end()); //o(n)
  }
  return path;
}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name){
  /*reference:"cpp tour - distance_matrix.cc" 
  * https://www.cnblogs.com/xzxl/p/7232929.html
  */
  // O(mn). n-length of data, m-edges in the graph
  std::vector<std::string> path;
  std::unordered_map<std::string, double> dist; //distance map of the nodes
  std::string start, end; // the id of location1 and location2
  std::unordered_map<std::string, std::string> pre; //record the node and its predecessor
  int len = data.size();

  //initialize the distance map. o(n)
  for (auto &i:data){
    dist[i.first] = INT_MAX;
    if (i.second.name == location1_name) {start = i.first;}
    if (i.second.name == location2_name) {end = i.first;}
  }
  dist[start] = 0; //the distance between start and start is 0

  for (int i=0; i<len-1; i++){ //there are n nodes, O(n)
    int flag = 0;
    for (auto &v:data){
      std::string node = v.first;
      for (auto &neigh:v.second.neighbors){ //two for loop: O(m)
        double d = sqrt(pow(v.second.lat-data[neigh].lat,2)+pow(v.second.lon-data[neigh].lon,2));
        if (dist[node] > dist[neigh] + d){
          dist[node] = dist[neigh] + d;
          pre[node] = neigh; //update the predecessor of the node
          flag = 1;
        }
      }
    }
    if (flag == 0){break;} //if there is no change, achieve balance. break
  }

  if (pre.find(end) != pre.end()){
      std::string temp = end;
      while (temp != start){
        path.push_back(temp);
        temp = pre[temp];
      }
      path.push_back(start);
      std::reverse(path.begin(), path.end());
    }

  return path;
}

/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */
// using backtracking
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan(
                                    std::vector<std::string> &location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> results;
  std::vector<std::vector<std::string>> res_vec;
  std::vector<std::string> optimal_path;
  //std::vector<std::string> current_path;
  double pathlen = INT_MAX, cur_len = 0; //minimal length
  //current_path.push_back(location_ids[0]);
  //location_ids.push_back(location_ids[0]); //route needs to go back to the starting point
  //backtrack will totally be invoked O(n!), push_back O(n). tatal:O(n*n!)
  //backtrack(location_ids, res_vec, pathlen, optimal_path, current_path);
  backtrack(location_ids, res_vec, 1, cur_len, pathlen, optimal_path);
  res_vec.push_back(optimal_path);
  results = std::make_pair(pathlen, res_vec);
  return results;
}

void TrojanMap::backtrack(std::vector<std::string> &points, std::vector<std::vector<std::string>> &res, 
                          int current, double &cur_len, double &pathlen, std::vector<std::string> &optimal_path){
  //reference - lc46
  //stable state
  if (current == points.size()){
    double templen = CalculateDistance(points[current-1], points[0]); //it's a circle!
    if (templen+cur_len < pathlen){
      pathlen = templen + cur_len;
      optimal_path = points;
      optimal_path.push_back(points[0]);
      res.push_back(optimal_path); //records O(n)
    }
    return;
  }

  for (int i=current; i<points.size(); i++){
    double templen2 = CalculateDistance(points[current-1], points[i]);
    if (cur_len + templen2 < pathlen){ //early backtrack
      cur_len += templen2; //add the next distance
      std::swap(points[current], points[i]); //O(1), swap two elements
      backtrack(points, res, current+1, cur_len, pathlen, optimal_path);
      std::swap(points[current], points[i]); //revoke swap
      cur_len -= templen2; //revoke the add
    }
  }
}


/*
void TrojanMap::backtrack(std::vector<std::string> &points, std::vector<std::vector<std::string>> &res, 
                          double &pathlen, std::vector<std::string> &optimal_path, std::vector<std::string> &current_path){
  //reference - lc46
  //stable state
  if (current_path.size() == points.size()){
    current_path.push_back(points[0]);
    double templen = CalculatePathLength(current_path);
    if (templen < pathlen){
      pathlen = templen;
      optimal_path = current_path;
      res.push_back(current_path); //records O(n)
    }
    current_path.pop_back();
    return;
  }

  if (CalculatePathLength(current_path)>=pathlen) {return;} // Early backtracking

  for (int i=1; i<points.size(); i++){
    if (std::find(current_path.begin(), current_path.end(), points[i]) == current_path.end()){
      current_path.push_back(points[i]);
      backtrack(points, res, pathlen, optimal_path, current_path);
      current_path.pop_back();
    }
  }
}
*/
//brute force
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_bruteforce(
                                    std::vector<std::string> &location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> results;
  std::vector<std::vector<std::string>> res_vec;
  std::vector<std::string> optimal_path;
  double pathlen = INT_MAX; //minimal length
  location_ids.push_back(location_ids[0]); //route needs to go back to the starting point
  //backtrack will totally be invoked O(n!), push_back O(n). tatal:O(n*n!)
  backtrack_bruteforce(location_ids, res_vec, 1, pathlen, optimal_path);
  res_vec.push_back(optimal_path);
  results = std::make_pair(pathlen, res_vec);
  return results;
}

/*bruteforce*/
void TrojanMap::backtrack_bruteforce(std::vector<std::string> &points, std::vector<std::vector<std::string>> &res, 
                          int current, double &pathlen, std::vector<std::string> &optimal_path){
  //reference - lc46
  //stable state
  if (current == points.size()-1){
    double templen = CalculatePathLength(points);
    if (templen < pathlen){
      pathlen = templen;
      optimal_path = points;
      res.push_back(points); //records O(n)
    }
    return;
  }

  for (int i=current; i<points.size()-1; i++){
    std::swap(points[current], points[i]); //O(1), swap two elements
    backtrack_bruteforce(points, res, current+1, pathlen, optimal_path);
    std::swap(points[current], points[i]); //revoke swap
  }
}


std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(
      std::vector<std::string> &location_ids){
  
  // reference: https://en.wikipedia.org/wiki/2-opt 
  // two for-loops to get (i,k), 2-opt swap(may not get the optimal answer!)
  // much faster!
  std::pair<double, std::vector<std::vector<std::string>>> results;
  location_ids.push_back(location_ids[0]);
  std::vector<std::vector<std::string>> res_vec; //all the path
  std::vector<std::string> optimal_path = location_ids;
  int len=location_ids.size();
  double current_dist = CalculatePathLength(location_ids);
  double pathlen = current_dist;
  
  while (true){
    int flag = 0;
    for (int i=1; i<len-2; i++){
      for (int k=i+1; k<len-1; k++){
        std::reverse(location_ids.begin()+i, location_ids.begin()+k+1);
        current_dist = CalculatePathLength(location_ids);
        if (current_dist < pathlen){
          pathlen = current_dist;
          optimal_path = location_ids;
          flag = 1;
          res_vec.push_back(location_ids);
        }
        else{std::reverse(location_ids.begin()+i, location_ids.begin()+k+1);}
      }
    }
    if (flag == 0){break;}
  }
  res_vec.push_back(optimal_path);
  results = std::make_pair(pathlen, res_vec);
  return results;
}

//aux function of 3-opt
double TrojanMap::CalculateDistance_3opt(const std::string &a_id, const std::string &b_id){
  return sqrt(pow(data[a_id].lat-data[b_id].lat,2)+pow(data[a_id].lon-data[b_id].lon,2));
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_3opt(
      std::vector<std::string> &location_ids){
  // reference1: http://tsp-basics.blogspot.com/2017/03/3-opt-move.html 
  // reference2: http://tsp-basics.blogspot.com/2017/03/3-opt-iterative-general-idea.html

  std::pair<double, std::vector<std::vector<std::string>>> results;
  std::vector<std::vector<std::string>> res_vec; //all the path
  if (location_ids.size() == 2){
    location_ids.push_back(location_ids[0]);
    results.second.push_back(location_ids);
    results.first = CalculatePathLength(results.second[0]);
  } 

  int opt3_case = 0, N = location_ids.size();
  // location_ids.push_back(location_ids[0]);
  // double min_length = CalculatePathLength(location_ids);
  double gain_length; //the minimal length of the path
  std::string x1, x2, y1, y2, z1, z2;
  std::string start = location_ids[0];
  int move1, move2, move3;
  bool flag = 1;

  while (flag){
    //first there for - loop, make x1<y1<z1 or y1<z1<x1 or z1<x1<y1
    flag = 0;
    for (int i=1; i<=N-1; i++){
      move1 = i;
      x1 = location_ids[i];
      x2 = location_ids[(i+1) % N];

      for (int j=1; j<= N-1; j++){
        move2 = (move1+j) % N;
        y1 = location_ids[move2];
        y2 = location_ids[(move2+1)%N];

        for (int k=j+1; k<=N-1; k++){
          move3 = (move1+k) % N;
          z1 = location_ids[move3];
          z2 = location_ids[(move3+1)%N];

          for (opt3_case=0; opt3_case<=7; opt3_case++){
            gain_length = gain_from_3opt(x1, x2, y1, y2, z1, z2, opt3_case);
            
            if (gain_length > 1e-15){
              move_3opt(location_ids, move1, move2, move3, opt3_case, x1, x2, y1, y2, z1, z2, N);
              res_vec.push_back(location_ids);
              res_vec[res_vec.size()-1].push_back(location_ids[0]);
              flag = 1;
              break;
            }
            
          }
          if (flag==1) {break;}
        }
        if (flag==1) {break;}
      }
      if (flag==1) {break;}
    }
  }

  int count = 0;
  for (auto i:location_ids){
    if (i==start) {break;}
    count ++;
  }
  
  std::vector<std::string> final_result;
  for (int i=count; i<count+N; i++){
    final_result.push_back(location_ids[i%N]);
  }

  final_result.push_back(start);
  res_vec.push_back(final_result);
  results = std::make_pair(CalculatePathLength(final_result), res_vec);
  return results;
}

int TrojanMap::getindex(std::vector<std::string> &v, std::string s){
  for (int i=0; i<v.size(); i++){
    if (v[i] == s){
      return i;
    }
  }
  return 0;
}

//aux function of 3-opt
void TrojanMap::move_3opt(std::vector<std::string> &location_ids, int move1, int move2, int move3, int opt3_case, 
                std::string x1, std::string x2, std::string y1, std::string y2, std::string z1, std::string z2 ,int N){
  int x2_index, y1_index, z1_index, y2_index;
  switch (opt3_case)
  {
  case 0:
    break;
  case 1:
    if ((move3+1)%N <= move1) {std::reverse(location_ids.begin()+(move3+1)%N, location_ids.begin()+move1+1);}
    else {std::reverse(location_ids.begin()+(move1+1)%N, location_ids.begin()+(move3+1)%N);}
    break;

  case 2:
    if ((move2+1)%N <= move3) {std::reverse(location_ids.begin()+(move2+1)%N, location_ids.begin()+move3+1);}
    else {std::reverse(location_ids.begin()+(move3+1)%N, location_ids.begin()+(move2+1)%N);}
    break;

  case 3:
    if ((move1+1)%N <= move2) {std::reverse(location_ids.begin()+(move1+1)%N, location_ids.begin()+move2+1);}
    else {std::reverse(location_ids.begin()+(move2+1)%N, location_ids.begin()+(move1+1)%N);}
    break;

  case 4:
    if ((move2+1)%N <= move3) {std::reverse(location_ids.begin()+(move2+1)%N, location_ids.begin()+move3+1);}
    else {std::reverse(location_ids.begin()+(move3+1)%N, location_ids.begin()+(move2+1)%N);}

    x2_index = getindex(location_ids, x2);
    y1_index = getindex(location_ids, y1); //what should be reversed is the original index
    if (x2_index <= y1_index) {std::reverse(location_ids.begin()+x2_index, location_ids.begin()+y1_index+1);}
    else {std::reverse(location_ids.begin()+y1_index, location_ids.begin()+x2_index+1);}
    break;

  case 5:
    if ((move3+1)%N <= move1) {std::reverse(location_ids.begin()+(move3+1)%N, location_ids.begin()+move1+1);}
    else {std::reverse(location_ids.begin()+(move1+1)%N, location_ids.begin()+(move3+1)%N);}

    x2_index = getindex(location_ids, x2);
    y1_index = getindex(location_ids, y1);
    if (x2_index <= y1_index) {std::reverse(location_ids.begin()+x2_index, location_ids.begin()+y1_index+1);}
    else {std::reverse(location_ids.begin()+y1_index, location_ids.begin()+x2_index+1);}
    break;

  case 6:
    if ((move3+1)%N <= move1) {std::reverse(location_ids.begin()+(move3+1)%N, location_ids.begin()+move1+1);}
    else {std::reverse(location_ids.begin()+(move1+1)%N, location_ids.begin()+(move3+1)%N);}

    y2_index = getindex(location_ids, y2);
    z1_index = getindex(location_ids, z1);
    if (y2_index <= z1_index) {std::reverse(location_ids.begin()+y2_index, location_ids.begin()+z1_index+1);}
    else {std::reverse(location_ids.begin()+z1_index, location_ids.begin()+y2_index+1);}
    break;

  case 7:
    if ((move3+1)%N <= move1) {std::reverse(location_ids.begin()+(move3+1)%N, location_ids.begin()+move1+1);}
    else {std::reverse(location_ids.begin()+(move1+1)%N, location_ids.begin()+(move3+1)%N);}

    x2_index = getindex(location_ids, x2);
    y1_index = getindex(location_ids, y1);
    if (x2_index <= y1_index) {std::reverse(location_ids.begin()+x2_index, location_ids.begin()+y1_index+1);}
    else {std::reverse(location_ids.begin()+y1_index, location_ids.begin()+x2_index+1);}

    y2_index = getindex(location_ids, y2);
    z1_index = getindex(location_ids, z1);
    if (y2_index <= z1_index) {std::reverse(location_ids.begin()+y2_index, location_ids.begin()+z1_index+1);}
    else {std::reverse(location_ids.begin()+z1_index, location_ids.begin()+y2_index+1);}
    break;
  }
}

//aux function of 3-opt
double TrojanMap::gain_from_3opt(std::string x1, std::string x2, std::string y1, std::string y2, 
                  std::string z1, std::string z2, int opt3_case){
  double del_length, add_length; //del_length<0; add_length>=0

  switch (opt3_case)
  {
  case 0:
    return 0;
  case 1:
    del_length = CalculateDistance_3opt(x1, x2) + CalculateDistance_3opt(z1, z2);
    add_length = CalculateDistance_3opt(x1, z1) + CalculateDistance_3opt(x2, z2);
    break;
  case 2:
    del_length = CalculateDistance_3opt(y1, y2) + CalculateDistance_3opt(z1, z2);
    add_length = CalculateDistance_3opt(y1, z1) + CalculateDistance_3opt(y2, z2);
    break;
  case 3:
    del_length = CalculateDistance_3opt(x1, x2) + CalculateDistance_3opt(y1, y2);
    add_length = CalculateDistance_3opt(x1, y1) + CalculateDistance_3opt(x2, y2);
    break;
  case 4:
    add_length = CalculateDistance_3opt(x1,y1) + CalculateDistance_3opt(x2,z1) + CalculateDistance_3opt(y2,z2);
    del_length = CalculateDistance_3opt(x1,x2) + CalculateDistance_3opt(y1,y2) + CalculateDistance_3opt(z1,z2);
    break;
  case 5:
    add_length = CalculateDistance_3opt(x1,z1) + CalculateDistance_3opt(y2,x2) + CalculateDistance_3opt(y1,z2);
    del_length = CalculateDistance_3opt(x1,x2) + CalculateDistance_3opt(y1,y2) + CalculateDistance_3opt(z1,z2);
    break;
  case 6:
    add_length = CalculateDistance_3opt(x1,y2) + CalculateDistance_3opt(z1,y1) + CalculateDistance_3opt(x2,z2);
    del_length = CalculateDistance_3opt(x1,x2) + CalculateDistance_3opt(y1,y2) + CalculateDistance_3opt(z1,z2);
    break;
  case 7:
    add_length = CalculateDistance_3opt(x1,y2) + CalculateDistance_3opt(z1,x2) + CalculateDistance_3opt(y1,z2);
    del_length = CalculateDistance_3opt(x1,x2) + CalculateDistance_3opt(y1,y2) + CalculateDistance_3opt(z1,z2);
    break;
  }
  return (del_length-add_length); //being positive indicates that the path can still be improved
}


// Genetic algorithm
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Genetic(
      std::vector<std::string> &location_ids){
  //reference - https://www.geeksforgeeks.org/traveling-salesman-problem-using-genetic-algorithm/
  //location_ids: gene. results: chromosome/population
  std::pair<double, std::vector<std::vector<std::string>>> results;
  if (location_ids.size() == 2){
    location_ids.push_back(location_ids[0]);
    results.second.push_back(location_ids);
    results.first = CalculatePathLength(results.second[0]);
  } 
  int population_size = 7, len = location_ids.size()+1; //initialize 10 permutations of cities
  std::vector<std::vector<std::string>> population; //record permutations
  std::vector<std::string> optimal_path;
  double min_path_len = INT_MAX;
  std::vector<std::vector<std::string>> res_vec;
  location_ids.push_back(location_ids[0]);

  for (int i=0; i<population_size; i++){
    //shuffle the nodes except the start and end. every shuffle means a population
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (location_ids.begin()+1, location_ids.end()-1, std::default_random_engine(seed));
    population.push_back(location_ids);
    //res_vec.push_back(location_ids);
    double d = CalculatePathLength(location_ids);
    // initialize the optimal path and its length
    if (d< min_path_len){
      optimal_path = location_ids;
      min_path_len = d;
    }
  }

  int temperature = 10000, gen=0; //genernations

  while (temperature > 500 && gen<7){
    std::vector<std::string> temp_len;

    // all populations need to be updated
    for (int i=0; i<population_size; i++){
      temp_len = population[i];
      while (true){

        //mutation(swap the elements)
        int j = (rand()%(len-2))+1, k=1; //[1,population_size-2]
        while (true){
          k = (rand()%(len-2))+1;
          if (j!=k){break;}
        }
        std::swap(temp_len[j], temp_len[k]);

        //update
        double dis_origin = CalculatePathLength(population[i]);
        double dis_new = CalculatePathLength(temp_len);
        if (dis_origin > dis_new){
          population[i] = temp_len;
          //res_vec.push_back(temp_len);
          if (dis_new < min_path_len) {
            min_path_len = dis_new;
            optimal_path = temp_len;
            res_vec.push_back(temp_len);
          }
          break;
        }

        // Accepting the rejected population at a possible probability above threshold.
        else{
          float prob = pow(2.7,-1 * ((float)(dis_new- dis_origin)/ temperature));
          if (prob > 0.5){
            population[i] = temp_len;
            res_vec.push_back(temp_len);
            break;
          }
        }
      }
    }
    temperature = (90*temperature)/100;
    gen++;
  }

  res_vec.push_back(optimal_path);
  results = std::make_pair(min_path_len, res_vec);
  return results;
}


/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations 
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(std::string locations_filename){
  std::vector<std::string> location_names_from_csv;
  std::fstream fin;
  fin.open(locations_filename, std::ios::in); // absolute path!
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);
    getline(s, word, ',');
    location_names_from_csv.push_back(word);
  }
  fin.close();
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(std::string dependencies_filename){
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::fstream fin;
  fin.open(dependencies_filename, std::ios::in); // absolute path!
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);
    std::vector<std::string> str_temp;
    while (getline(s, word, ',')) {
      str_temp.push_back(word);
    }
    dependencies_from_csv.push_back(str_temp);
  }
  fin.close();
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a sorting of nodes
 * that satisfies the given dependencies.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,
                                                     std::vector<std::vector<std::string>> &dependencies){
  //reference - https://www.geeksforgeeks.org/topological-sorting/
  std::vector<std::string> result;
  if (locations.size()==0) {return result;}
  if (dependencies.size() ==0) {return locations;}

  //std::stack<std::string> res_stack;
  std::unordered_map<std::string, int> mark;
  std::unordered_map<std::string, std::vector<std::string>> edge_map;

  //initialize edge_map and mark
  for (auto &i:locations){
    edge_map[i] = {};
    mark[i] = 0;
  }
  for (auto &j:dependencies){
    for (int i=1; i<j.size(); i++){
      edge_map[j[0]].push_back(j[i]);
    }
  }

  // recursivly access all the nodes
  for (auto &i:locations){
    if (mark[i]==0){ //to ensure every node can be accessed
      DFS_TS(result, mark, i, edge_map);
    }
  }

  // result is like a stack, the deepest node comes first. so need to reverse
  std::reverse(result.begin(), result.end());
  return result;                                                     
}

void TrojanMap::DFS_TS(std::vector<std::string> &result, std::unordered_map<std::string, int> &mark,
        std::string root, std::unordered_map<std::string, std::vector<std::string>> &edge_map){
  mark[root] = 1; //record the visited node
  for (auto neighbor : edge_map[root]){ //directed graph
    if (mark[neighbor] != 1){
      DFS_TS(result, mark, neighbor, edge_map);
    }
  }
  result.push_back(root); //push back the deepest nodes
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 * 
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */

bool TrojanMap::DFS(std::string id,std::map<std::string,bool> &visited,std::string parent,std::vector<std::string> &path){
    visited[id] = true;
    Node n = data[id];
    for (std::string nei : n.neighbors){
        if (visited.count(nei)>0){
          if (!visited[nei]){
            if (DFS(nei,visited,id,path)){
              path.push_back(id);
              return true;
            }
          }
          else {
            if (nei != parent){
              path.push_back(id);
              return true;
            }
          }
      }
      
    }
    return false;
  }
bool TrojanMap::CycleDetection(std::vector<double> &square) {
  std::vector<std::string> points; //nodes in this square
  std::vector<std::string> path;
  double left = square[0];
  double right = square[1];
  double upper = square[2];
  double lower = square[3];
  
  for(auto &i:data){
    if(i.second.lon>left && i.second.lon<right && i.second.lat>lower && i.second.lat<upper){
      points.push_back(i.first);
    }
  }

  std::map<std::string,bool> visited;
  for (std::string i:points){
    visited[i] = false;
  }

  for (std::string i:points){
    if (!visited[i]){
      if (DFS(i,visited,"",path)){
        PlotPointsandEdges(path,square);
        return true;
      }
    }
  }
  return false;
}

/**
 * FindKClosetPoints: Given a location id and k, find the k closest points on the map
 * 
 * @param {std::string} name: the name of the location
 * @param {int} k: number of closest points
 * @return {std::vector<std::string>}: k closest points
 */
std::vector<std::string> TrojanMap::FindKClosestPoints(std::string name, int k) {
  //using heap! O(nlogk)
  std::vector<std::string> res;
  std::priority_queue<std::pair<double, std::string>> q; // first element is maximum 
  std::string start_id = GetID(name);
  //double start_lat = data[start_id].lat;
  //double start_lon = data[start_id].lon;
  int count =0;

  // limit the size of priority_queue to k
  for (auto &v:data){
    Node n = v.second;
    if (v.first != start_id && n.name.size()!=0){
      //double d = sqrt(pow(n.lat-start_lat,2)+pow(n.lon-start_lon,2)); ？？？？wrong
      double d = CalculateDistance(v.first, start_id);
      if (count < k){
        q.push(std::make_pair(d, v.first));
        count ++;
      }
      else{
        if (d < q.top().first){
          q.pop();
          q.push(std::make_pair(d, v.first));
        }
      }
    }
  }

  while (!q.empty()){
    res.push_back(q.top().second);
    std::cout << q.top().second<<": "<<q.top().first<<std::endl;
    q.pop();
  }
  std::reverse(res.begin(), res.end());
  return res;
}