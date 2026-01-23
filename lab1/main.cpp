#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

class Robot {
private:
    double x, y, heading;
    std::string name;
    std::vector<double> sensorReadings;

public:
    Robot(const std::string& robotName, double startX = 0.0, double startY = 0.0)
        : name(robotName), x(startX), y(startY), heading(0.0) {}

    void move(double distance) {
        x += distance * std::cos(heading);
        y += distance * std::sin(heading);
    }

    void turn(double angle) {
        heading += angle;
        while (heading > M_PI) heading -= 2 * M_PI;
        while (heading < -M_PI) heading += 2 * M_PI;
    }

    void addSensorReading(double value) {
        sensorReadings.push_back(value);
        if (sensorReadings.size() > 100) {
            sensorReadings.erase(sensorReadings.begin());
        }
    }

    double getAverageSensorReading() const {
        if (sensorReadings.empty()) return 0.0;
        double sum = 0.0;
        for (const auto& reading : sensorReadings) {
            sum += reading;
        }
        return sum / sensorReadings.size();
    }

    void printStatus() const {
        std::cout << "Robot: " << name << "\n";
        std::cout << "Position: (" << x << ", " << y << ")\n";
        std::cout << "Heading: " << heading * 180.0 / M_PI << " degrees\n";
        std::cout << "Sensor readings: " << sensorReadings.size() << "\n";
    }

    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getHeading() const { return heading; }
    std::string getName() const { return name; }
};

struct Waypoint {
    double x, y;
    double tolerance;
    std::string label;

    bool isReached(double robotX, double robotY) const {
        double dx = robotX - x;
        double dy = robotY - y;
        return std::sqrt(dx * dx + dy * dy) <= tolerance;
    }
};

class PathPlanner {
private:
    std::vector<Waypoint> waypoints;
    size_t currentIndex;

public:
    PathPlanner() : currentIndex(0) {}

    void addWaypoint(double x, double y, double tolerance, const std::string& label) {
        waypoints.push_back({x, y, tolerance, label});
    }

    Waypoint* getCurrentWaypoint() {
        if (currentIndex < waypoints.size()) {
            return &waypoints[currentIndex];
        }
        return nullptr;
    }

    bool advanceWaypoint() {
        if (currentIndex < waypoints.size() - 1) {
            currentIndex++;
            return true;
        }
        return false;
    }

    void reset() {
        currentIndex = 0;
    }

    size_t getWaypointCount() const {
        return waypoints.size();
    }
};

int main() {
    Robot myRobot("TestBot", 0.0, 0.0);
    PathPlanner planner;

    planner.addWaypoint(10.0, 0.0, 0.5, "First");
    planner.addWaypoint(10.0, 10.0, 0.5, "Second");
    planner.addWaypoint(0.0, 10.0, 0.5, "Third");
    planner.addWaypoint(0.0, 0.0, 0.5, "Home");

    for (int i = 0; i < 50; i++) {
        myRobot.move(0.5);
        myRobot.addSensorReading(static_cast<double>(i) * 0.1);

        if (i % 10 == 0) {
            myRobot.turn(M_PI / 2);
        }

        Waypoint* target = planner.getCurrentWaypoint();
        if (target && target->isReached(myRobot.getX(), myRobot.getY())) {
            std::cout << "Reached waypoint: " << target->label << "\n";
            planner.advanceWaypoint();
        }
    }

    myRobot.printStatus();
    std::cout << "Average sensor reading: " << myRobot.getAverageSensorReading() << "\n";

    return 0;
}