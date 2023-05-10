# include <exception>
# include <string>

using namespace std;

class Exception: public exception{

  private:
    int number;               // Number of the 'Error'
    string phrase;            // Description of the 'Error'
    int level;               // 'Error' level

  public:
    Exception(int e_number = 0, string const &e_phrase = "", int e_level = 0) throw(): number(e_number), phrase(e_phrase), level(e_level){
      /*
      Class constructor 'Exception'.
      */
    }

    virtual const char* what() const noexcept{
      /*
      Method to get the message associated with the 'Exception'.
      */
      return phrase.c_str();
    }

    int getLevel() const noexcept{
      /*
      Getter method to 'level' attribute.
      */
      return level;
    }

    int getNumber() const noexcept{
      /*
      Getter method to 'number' attribute.
      */
      return number;
    }

    virtual ~Exception() noexcept{
      /*
      Class desctructor 'Exception'.
      */
    }
  };
