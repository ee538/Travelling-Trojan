#include <map>
#include <vector>
#include <unordered_set>
#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

//Test Step1: Autocomplete the location name
TEST(TrojanMapStudentTest, Test1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // groundtruth for "Sa"(simple case)
  auto names = m.Autocomplete("Sa");
  std::unordered_set<std::string> gt1 = {"Saint James Park", "Saint Agnes Elementary School","Safety Pole","Saint Marks Lutheran Church"}; 
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt1.count(n) > 0, true);
    if (gt1.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt1.size());  

  // groundtruth for "sa"(lower case)
  names = m.Autocomplete("sa");
  std::unordered_set<std::string> gt2 = {"Saint James Park", "Saint Agnes Elementary School","Safety Pole","Saint Marks Lutheran Church"}; 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt2.count(n) > 0, true);
    if (gt2.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt2.size());

  // groundtruth for "sA"(Upper and lower case)
  names = m.Autocomplete("sA");
  std::unordered_set<std::string> gt3 = {"Saint James Park", "Saint Agnes Elementary School","Safety Pole","Saint Marks Lutheran Church"}; 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt3.count(n) > 0, true);
    if (gt3.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt3.size());

  // roundtruth for "SA"(Upper and lower case) 
  names = m.Autocomplete("SA"); 
  std::unordered_set<std::string> gt4 = {"Saint James Park", "Saint Agnes Elementary School","Safety Pole","Saint Marks Lutheran Church"};
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt4.count(n) > 0, true);
    if (gt4.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt4.size());
}

// Test Step2: Find the place's coordinates in the map
TEST(TrojanMapTest, FindPosition) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test Coffee Bean1
  auto position = m.GetPosition("Coffee Bean1");
  // groundtruth for "Coffee Bean1"
  std::pair<double, double> gt1(34.0172407, -118.2824946); 
  EXPECT_EQ(position, gt1);
  // Test The Row House
  position = m.GetPosition("The Row House");
  //groundtruth for "The Row House"
  std::pair<double, double> gt2(34.0263672, -118.2785935); 
  EXPECT_EQ(position, gt2);
  // Test Department of Motor Vehicles
  position = m.GetPosition("Department of Motor Vehicles");
  // groundtruth for "Department of Motor Vehicles"
  std::pair<double, double> gt3(34.0180476, -118.2791616); 
  EXPECT_EQ(position, gt3);
  // Test Unknown
  position = m.GetPosition("XXX");
  std::pair<double, double> gt4(-1, -1);
  EXPECT_EQ(position, gt4);
}

// Test Step3: CalculateShortestPath Dijkstra and Bellman_Ford function 1
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from ExpoVermont to JeffersonUSC
  auto path = m.CalculateShortestPath_Bellman_Ford("ExpoVermont", "JeffersonUSC");
  std::vector<std::string> gt{
      // Expected path
      "4400281325", "6813379567", "123112726", "6813379571", "7023424984", "123112725", "4015405540",
      "213431695", "7023430193", "213431822", "7023424981", "441891112", "932401855", "4015405541",
      "6820935897", "1781230449", "4015405542", "4015405543", "1837212104","123112723", "6813405278", "348121864",
      "348121996", "6813411585", "4015405552", "4399914028", "6820972462", "269633270", "4015405553", 
      "4399914049", "5472460620", "214470792", "1841835270", "4011837222", "1841835282", "4400281328",}; 
      
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from JeffersonUSC to ExpoVermont
  path = m.CalculateShortestPath_Dijkstra("JeffersonUSC", "ExpoVermont");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test Step3: CalculateShortestPath Dijkstra and Bellman_Ford function 2
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from 7Eleven to Lyons Center
  auto path = m.CalculateShortestPath_Bellman_Ford("7Eleven", "Lyons Center");
  // Expected path
  std::vector<std::string> gt{
      "5695236165", "3438433461", "4835551077", "4835551072", "5680945537", "123241961", "6813565326", 
      "4012842277", "4835551064", "5556117115", "5556117120", "20400292", "6813513564", "6813513563", 
      "122659187", "7863689395", "4835551084", "2613117900", "7863656075", "7863689388", "6807580191", 
      "6787803674", "6787803666", "6787803661", "6787803658", "6787803653", "6787803649", "6816822864", "122659191",
      "2613117891", "6813379507", "6985903602", "6813416161", "122814440", "6813416162", "2613117899", "7601578291", 
      "6813379508", "122719213", "6813379510", "441895675", "4399698024", "4399698025", "214470797", "4399698026", 
      "4399698027", "6813405233", "122719216", "6813405231", "2613117893", "122719255","7591500905", "7591500900",
      "7591500901", "7591500902", "7591500903", "7591500907", "7591500904", "7591500906","1849116066", "1849116072", 
      "1849116069", "6229624525", "1849116060", "6047218633","1849116064", "1849116062", "1849116067", "6813379474",
      "63068610", "6818390139","1286136450", "6818390142", "6813379477", "1286136425", "4015423967", "1286136467",
      "1286136465", "6808200832","6042952605" }; 
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Lyons Center to 7Eleven
  path = m.CalculateShortestPath_Dijkstra("Lyons Center","7Eleven");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test Step3: CalculateShortestPath Dijkstra and Bellman_Ford function 3
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Los Angeles to Parking Center
  auto path = m.CalculateShortestPath_Bellman_Ford("Los Angeles", "Parking Center");
  // Expected path
  std::vector<std::string> gt{
      "368173251", "7360424709", "269636455", "269636427", "269636426", "269635137", "5768963619", 
      "5768963620", "1613487058", "269635440", "269635411", "1614922628", "1614922626", "4399914044", 
      "4399914043", "1614922624", "4399914042", "1614922622", "4399914035", "1614922617", "1837202710", 
      "1837202714", "4399914037", "4399914040", "1837202706", "123292047", "6939732877", "123292045", "4012759747",
      "4012759746", "732642214" }; 
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Parking Center to Los Angeles
  path = m.CalculateShortestPath_Dijkstra("Parking Center","Los Angeles");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test Step4: The traveling Trojan Problem function 1
TEST(TrojanMapTest, TSP) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"63785495", "123178896", "123660671", "6813379466"}; // Input location ids 
  // auto result = m.TravellingTrojan(input);
  auto result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"63785495", "6813379466", "123660671", "123178896", "63785495"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}

// Test Step4: The traveling Trojan Problem function 2
TEST(TrojanMapTest, TSP2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"123178896", "123302797", "7668796165", "1837206580", "4020099357", "7771782317"}; // Input location ids 
  // auto result = m.TravellingTrojan(input); 
  auto result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"123178896", "1837206580", "4020099357", "7668796165", "123302797","7771782317",  "123178896"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}

// Test Step4: The traveling Trojan Problem function 3
TEST(TrojanMapTest, TSP3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"5567733799", "6817111153", "4012693772", "4012726926", "6047204780", "6816180156", "123178873", "3574052697", "123715912", "6503044367"}; // Input location ids 
  auto result = m.TravellingTrojan(input);
  // auto result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: " <<result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"5567733799", "6047204780", "6503044367", "4012726926", "123715912", "3574052697", "4012693772", "6817111153", "6816180156", "123178873", "5567733799"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  
  EXPECT_EQ(flag, true);
}

// Test Step5: Cycle detection function
TEST(TrojanMapTest, CycleDetection) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test case 1
  std::vector<double> square1 = {-118.278,-118.267,34.028,34.015};
  bool result1 = m.CycleDetection(square1);
  EXPECT_EQ(result1, true);

  // Test case 2
  std::vector<double> square2 = {-118.294, -118.265, 34.031, 34.012};
  bool result2 = m.CycleDetection(square2);
  EXPECT_EQ(result2, true);

  // Test case 3
  std::vector<double> square3 = {-118.290, -118.286, 34.025, 34.020};
  bool result3 = m.CycleDetection(square3);
  EXPECT_EQ(result3, false);
}

// Test Step6: Topological Sort
TEST(TrojanMapTest, TopologicalSort) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  //test case 1
  std::vector<std::string> location_names1 = {"University Park", "Troy View Swimming Pool","CVS"};
  std::vector<std::vector<std::string>> dependencies1 = {{"University Park","Troy View Swimming Pool"}, {"Troy View Swimming Pool","CVS"}, {"University Park","CVS"}};
  auto result1 = m.DeliveringTrojan(location_names1, dependencies1);
  std::vector<std::string> gt1 ={"University Park", "Troy View Swimming Pool","CVS"};
  EXPECT_EQ(result1, gt1);
  //test case 2
  std::vector<std::string> location_names2 = {"Workshop Salon 38 Boutique", "USC Village Dining Hall","Coffee Bean2"};
  std::vector<std::vector<std::string>> dependencies2 = {{"Workshop Salon 38 Boutique","USC Village Dining Hall"}, {"USC Village Dining Hall","Coffee Bean2"}, {"Workshop Salon 38 Boutique","Coffee Bean2"}};
  auto result2 = m.DeliveringTrojan(location_names2, dependencies2);
  std::vector<std::string> gt2 ={"Workshop Salon 38 Boutique", "USC Village Dining Hall","Coffee Bean2"};
  EXPECT_EQ(result2, gt2);
  //test case 3
  std::vector<std::string> location_names3 = {"Saint Marks Lutheran Church", "Trinity Elementary School","Ralphs"};
  std::vector<std::vector<std::string>> dependencies3 = {{"Saint Marks Lutheran Church","Trinity Elementary School"}, {"Saint Marks Lutheran Church","Ralphs"}, {"Trinity Elementary School","Ralphs"}};
  auto result3 = m.DeliveringTrojan(location_names3, dependencies3);
  std::vector<std::string> gt3 ={"Saint Marks Lutheran Church", "Trinity Elementary School","Ralphs"};
  EXPECT_EQ(result3, gt3);
}

// Test Step7: Find K closest points
TEST(TrojanMapTest, FindKClosestPoints) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  //test case 1
  auto result1 = m.FindKClosestPoints("Crosswalk1",5);
  std::vector<std::string> gt1{
  "6813416126", "358850043", "358850041", "6813405267","6987230635"};
  EXPECT_EQ(result1, gt1);
  //test case 2
  auto result2 = m.FindKClosestPoints("Moreton Fig",10);
  std::vector<std::string> gt2{
  "5229911615", "5229911604", "2305853437", "2305853438","4399693645", 
  "2817034894", "2817034895", "4399693644", "4536993737", "6474130386"};
  EXPECT_EQ(result2, gt2);
  //test case 3
  auto result3 = m.FindKClosestPoints("Parking Center",7);
  std::vector<std::string> gt3{
  "6939732877", "4400281328", "4732965439", "6655857589","6815182445", 
  "6206425701", "5231970321"};
  EXPECT_EQ(result3, gt3);
}


