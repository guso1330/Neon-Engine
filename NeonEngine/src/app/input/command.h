// SAMPLE FILE FROM: https://stackoverflow.com/questions/7624017/c0x-storing-any-type-of-stdfunction-in-a-stdmap

#include <functional>
#include <map>
#include <string>
#include <memory>

using namespace std;

class BaseCommand
{
  public:
    virtual ~BaseCommand() {}
};

template <class... ArgTypes>
class Command : public BaseCommand
{
  typedef std::function<void(ArgTypes...)> FuncType;
  FuncType f_;
  public:
    Command() {}
    Command(FuncType f) : f_(f) {}
    void operator()(ArgTypes... args) { if(f_) f_(args...); }
};

class CommandManager
{
  typedef shared_ptr<BaseCommand> BaseCommandPtr;
  typedef map<string, BaseCommandPtr> FMap;
  
  public:
    template <class T>
    void add(string name, const T& cmd)
    {
      fmap1.insert(pair<string, BaseCommandPtr>(name, BaseCommandPtr(new T(cmd))));
    }

    template <class... ArgTypes>
    void execute(string name, ArgTypes... args)
    {
      typedef Command<ArgTypes...> CommandType;
      FMap::const_iterator it = fmap1.find(name);
      if(it != fmap1.end())
      {
        CommandType* c = dynamic_cast<CommandType*>(it->second.get());
        if(c)
        {
          (*c)(args...);
        }
      }
    }

  private :
    FMap fmap1;
};
