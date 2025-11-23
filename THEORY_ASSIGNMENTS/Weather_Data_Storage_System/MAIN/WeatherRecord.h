#ifndef WEATHER_RECORD_H
#define WEATHER_RECORD_H

#include <string>
#include <iostream>

using namespace std;

class WeatherRecord {
private:
    string date;      // Date in format DD/MM/YYYY
    string city;      // City name
    double temperature; // Temperature reading

public:
    // Constructors
    WeatherRecord() : date(""), city(""), temperature(-999) {}
    
    WeatherRecord(const string& date, const string& city, double temp) 
        : date(date), city(city), temperature(temp) {}
    
    // Getters
    string getDate() const { return date; }
    string getCity() const { return city; }
    double getTemperature() const { return temperature; }
    
    // Extract year from date
    int getYear() const {
        if (date.length() < 4) return -1;
        return stoi(date.substr(date.length() - 4));
    }
    
    // Setters
    void setDate(const string& d) { date = d; }
    void setCity(const string& c) { city = c; }
    void setTemperature(double t) { temperature = t; }
    
    // Overload == operator for record comparison (based on city & date)
    bool operator==(const WeatherRecord& other) const {
        return (city == other.city && date == other.date);
    }
    
    // toString method for display
    string toString() const {
        return "Date: " + date + ", City: " + city + 
               ", Temperature: " + to_string(temperature);
    }
};

#endif // WEATHER_RECORD_H