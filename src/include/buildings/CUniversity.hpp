/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include "../CCell.hpp"
#include "../CPerson.hpp"

/**
 * University building
 * This class represents a University building cell 
 */
class CUniversity : public CCell
{
  public:

    /**
     * Constructor
     * Initializes the building's attributes
     * @param view the view of the building on map
     * @param maximumStudents the maximum number of students
     * @param graduationTime the time in 0.5s for the university to perform graduation
     */
    CUniversity(const std::string & view, unsigned maximumStudents, unsigned graduationTime);

    /**
     * Takes care of the building life updates
     * @param stats a reference to the game statistics that might be modified
     */
    virtual void update(CStatHandler & stats) override;

    /**
     * Gets the vector of building's menu options
     * @return vector of menu options
     */
    virtual std::vector<TMenu> getOptions() const override;

    /**
     * Gets the building information
     * @return the current information of the building
     */
    virtual std::string getInfo() const override;

    /**
     * Processes selected options
     * @param the selected option
     * @param a reference to the game statistics that might be modified 
     */
    virtual void proceedOptionClicked(int option, CStatHandler & stats) override;
    
    /**
     * Gets data of the building to be saved in a save file
     * @return a string of the data
     */
    virtual std::string getSaveData() const override;

    /**
     * Loads building data based on the given data
     * @param data a string of data to be loaded
     * @param stats a pointer to the game statistics that might be modified
     */
    virtual void loadSaveData(const std::string & data, CStatHandler * stats) override;

  private: 

    /**
     * Receivers new students
     * @param stats a reference to the game statistics
     */
    void hireNewStudents(CStatHandler & stats);

    /**
     * Performs graduation
     * Assigns professions to the students
     * @param stats a reference to the game statistics
     */
    void actionGraduate(CStatHandler & stats);

    /**
     * Removes students from school who are either dead or isolated
     * @param stats a reference to the game statistics
     */
    void removeDeadStudents(CStatHandler & stats);

    std::vector<TMenu> m_options;

    std::vector<CPerson*> m_students;

    unsigned m_maximumStudents;

    unsigned m_graduationTime;

    unsigned m_ctr;

    bool m_processGraduation;


};