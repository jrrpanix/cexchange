#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <numeric>
#include <boost/regex.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/algorithm/string/split.hpp> 
#include <boost/algorithm/string/trim.hpp> 
#include <boost/algorithm/string/classification.hpp> 
#include <boost/algorithm/string/case_conv.hpp> 
#include <boost/algorithm/string/erase.hpp> 
#include <boost/algorithm/string/replace.hpp> 
#include <boost/algorithm/string/predicate.hpp> 
#include <boost/lexical_cast.hpp> 
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/filesystem.hpp>
#include <boost/bind.hpp>


void fileTest() {
  using namespace boost::filesystem;
  path p("/home/jrr/git/vchan/src");
  if (exists(p)  && is_directory(p)) {
    std::cout << p << " exists" << std::endl;
  }
  for(auto itr = directory_iterator(p); itr != directory_iterator(); ++itr) {
    directory_entry e = *itr;
    int size = is_regular_file(e) ? file_size(e) : 0;
    std::cout << e.path().string() << ":" << size << ":" << e.path().extension().string() << std::endl;
  }
}

void dateTest() {
  boost::gregorian::date d(2019,01,01);
  std::cout << "date=" << d << ",julian_day="<< d.julian_day() << std::endl;
  boost::gregorian::months m(2);
  d += m;
  std::cout << "add " << m.number_of_months().as_number() << " months" << std::endl;
  std::cout << "date=" << d << ",julian_day="<< d.julian_day() << std::endl;
  boost::gregorian::date_duration dur(17);
  d += dur;
  std::cout << "add " << dur.days() << " days" << std::endl;
  std::cout << "date=" << d << ",julian_day="<< d.julian_day() << std::endl;
  boost::gregorian::years yr(8);
  d += yr;
  std::cout << "add " << yr.number_of_years().as_number() << " years" << std::endl;
  std::cout << "date=" << d << ",julian_day="<< d.julian_day() << std::endl;

  std::cout << "day:" << d.day()
	    << ",month:" << d.month()
	    << ",year:" << d.year()
	    << ",day_of_week:" << d.day_of_week()
	    << ",week_number:" << d.week_number()
	    << ",end_of_month:" << d.end_of_month()
	    << std::endl;
    
  
}



void stringTest() {
  std::string csv="A  ,B  ,C  ,D  ,E  ,F  \n";
  std::vector<std::string> sv;

  boost::split(sv, csv, boost::is_any_of(","));
  for_each(sv.begin(), sv.end(), [](std::string &x){boost::trim<std::string>(x);});
  for_each(sv.begin(), sv.end(), [](std::string &x){boost::to_lower<std::string>(x);});
  for_each(sv.begin(), sv.end(), [](const std::string &x) { std::cout << x << "|" <<std::endl;});

  std::string abc = "xxx543xxx212xxx8487";
  std::string abc1 = abc;
  std::string replace = "xxx";
  boost::replace_all(abc, replace, "");
  std::cout << "before:" << abc1 << ";replace:" << replace << ";after" << abc << std::endl;

  std::string s1= "ABC", s2 = "abc";
  std::cout << "boost::iequals(" << s1 << "," << s2 << ") = " << boost::iequals(s1, s2) << std::endl;
  
}


void diceTest(int trials , unsigned seed) {
  boost::mt19937 random_num_gen( seed );
  boost::uniform_int<> urange(1,6);
  boost::variate_generator< boost::mt19937 , boost::uniform_int<> > dice( random_num_gen , urange );

  int cnt[13];
  memset(&cnt[0], 0, sizeof(cnt));
  for(int i = 0; i < trials ; ++i) {
    int d1 = dice() , d2 = dice() , s = d1 + d2;
    cnt[s]++;
  }
  for (int i=2; i < 13; ++i)
    std::cout << i << ":" << cnt[i]/static_cast<double>(trials) << std::endl;
}


void normTest(double mean, double variance, long seed) {
  boost::mt19937 random_num_gen( seed );
  boost::normal_distribution<double> n_dist(mean,variance);
  boost::variate_generator< boost::mt19937 , boost::normal_distribution<double> > normal_rv( random_num_gen , n_dist );
  for (int i=0; i < 10; ++i)
    std::cout << normal_rv() << std::endl;
}


void regexTest() {
  boost::regex year("(1|2|3)[0-9][0-9][0-9]((0[1-9])|(1(0|1|2)))(0[1-9]|[1-2][[0-9]|3[0-1])");
  std::vector<std::string> tests = {"20190101", "20199999", "19642020", "19700512","20000628","19961214","20101233","20101200","20101231"};
  for(std::string t : tests) {
    boost::smatch matches;
    if (boost::regex_match(t, matches, year))
      std::cout <<"valid date:" << t << std::endl;
    else
      std::cout << "invalid  :" << t << std::endl;
  }
}

int rvalue_add(int &&x) {
  return x + 1;
}

int rvalue_sum(std::vector<int> &&x) {
  return std::accumulate(x.begin(), x.end(), 0);
}

int const_sum(const std::vector<int> &x) {
  return std::accumulate(x.begin(), x.end(), 0);
}

int rec_sum(int&& n) {
  if (n == 0) return 0;
  return n + rec_sum(n-1);
}

int walk_down(int n, int&& d) {
  n = std::max(0, n + d);
  std::cout << n << std::endl;
  if (n ==0) return 0;
  return walk_down(n, d < 0 ? 1 : -2);
}

void stst(std::string &&z) {
  std::cout << z << std::endl;
}

void rvalueTest() {
  // rvalue - we can't take its address, lvalue - we can take its address
  int x = 11;
  std::cout << rvalue_add(2) << std::endl;
  std::cout << rvalue_add(x + 2) << std::endl;
  std::cout << rvalue_sum({1,2,3}) << std::endl;
  std::cout << const_sum({1,2,3}) << std::endl;

  std::vector<int> z = {1,2,3,4};
  std::vector<int> y = std::move(z);
  std::cout << z.size() << " " << y.size() << std::endl;

  std::string a = "123456";
  std::string b = std::move(a);
  std::cout << a << " " << a.length() << " " << b << " " << b.length() << std::endl;
  a = std::move(b);
  std::cout << a << " " << a.length() << " " << b << " " << b.length() << std::endl;

  std::string &&c = "9876";
  std::string d = std::move(c);
  std::cout << c << " " << c.length() << " " << d << " " << d.length() << std::endl;

  std::cout << "sum n="<<5<<":" << rec_sum(5) << std::endl;
  walk_down(10, -2);

  stst(std::move(d));
  
}


int badd(int a, int b) {
  return a+b;
}

void bindTest() {

  auto v = boost::bind(badd, 3, _1);
  for (int i=0;i < 4; ++i)
    std::cout << i << ":" << v(i) << std::endl;
  
  auto z = boost::bind(badd, _1, _2)(1,2);
  std::cout << z << std::endl;

  
}


int main(int argc, char **argv) {
  regexTest();
  normTest(0,1,2312);
  diceTest(1000000, 4321);
  stringTest();
  dateTest();
  fileTest();
  rvalueTest();
  bindTest();
}
