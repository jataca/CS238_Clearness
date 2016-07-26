/***********************************************************************
 * Program:
 *    Exploration 2, Clearness
 *    Brother Neff, CS 238
 * Author:
 *    You
 * Summary:
 *    Amortization Calculating Program
 *    Exploring a practical recurrence relation.
 ***********************************************************************/
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

/***********************************************************************
 * Amortize class for amortization calculations.
 * See, for example:
 * http://www.bankrate.com/calculators/mortgages/mortgage-calculator.aspx
 *
 * DO NOT CHANGE ANYTHING IN THIS CLASS!
 ***********************************************************************/
class Amortize
{
private:
   int mTermInMonths;              // term in months (n)

   double mRate;                   // annual interest rate (r)

   double mPeriodicRate;           // periodic (monthly) rate (i)

   double mPrincipal;              // principal (p)

   double mMonthlyPayment;         // monthly payment (m)

   double mExtraMonthlyPayment;    // extra monthly payment (x)

   bool mShowAmortizationSchedule; // verbose (v)

   int mStart; // extra payment starting month number (s)

   int mEnd;   // extra payment ending month number (e)

   bool mHavePrincipal;      // p

   bool mHavePeriodicRate;   // r

   bool mHaveTermInMonths;   // n

   bool mHaveMonthlyPayment; // m

   /***********************************************************************
    * Find p given i, m, n.
    ***********************************************************************/
   void findPrincipal();

   /***********************************************************************
    * Find i given p, m, n.
    **********************************************************************/
   void findPeriodicRate();

   /***********************************************************************
    * Find m given p, i, n.
    **********************************************************************/
   void findMonthlyPayment();

   /***********************************************************************
    * Find n given p, i, m.
    **********************************************************************/
   void findTermInMonths();

   /***********************************************************************
    * Find all missing parameters.
    * Implemented below. 
    **********************************************************************/
   bool findAll();

   /****************************************************************
    * Check information for consistency.
    * Implemented below.
    ****************************************************************/
   bool checkConsistency();

   /****************************************************************
    * Displays the month, interest paid, principal paid and balance.
    * Implemented below.
    ****************************************************************/
   void showAmortizationLine(int month, double interestPaid,
                             double principalPaid,
                             double balance);

   /****************************************************************
    * When the balance goes negative, do the right thing;
    * Implemented below.
    ****************************************************************/
   bool balanceGoesNegative(double balance, double &principalPaid,
                            double &totalPaid);

public:
   /****************************************************************
    * Construct an Amortize instance.
    * Implemented below.
    ****************************************************************/
   Amortize(int termInMonths, double rate, double principal,
            double monthlyPayment, double extraMonthlyPayment,
            bool showAmortizationSchedule, int start, int end,
            bool havePrincipal, bool haveRate,
            bool haveTermInMonths, bool haveMonthlyPayment);

   /****************************************************************
    * Displays the month, interest paid, principal paid and balance.
    * Implemented below.
    ****************************************************************/
   void display();

   /****************************************************************
    * Conditionally runs with the data found (if consistent).
    * Implemented below.
    ****************************************************************/
   void run();
};


/***********************************************************************
 * Find p given i, m, n.
 * Finds the principal
 ***********************************************************************/
void Amortize::findPrincipal()
{
   mPrincipal = (mMonthlyPayment / mPeriodicRate) * (1 - pow(1 + mPeriodicRate, mTermInMonths * -1));
}

/***********************************************************************
 * Find i given p, m, n.
 * Finds the periodic rate and the annual rate
 **********************************************************************/
void Amortize::findPeriodicRate()
{
   double iMax = 1;
   double iMin = 0;
   
   double tempPrincipal = 0; 

   while (abs(tempPrincipal - mPrincipal) >= 0.01 )
   {
      mPeriodicRate = (iMax + iMin) / 2.0;
      tempPrincipal = (mMonthlyPayment / mPeriodicRate) * (1 - pow(1 + mPeriodicRate, mTermInMonths * -1));

      if (tempPrincipal > mPrincipal) 
      {
         iMin = mPeriodicRate;
      }
      else
      {
         iMax = mPeriodicRate;
      }  
   }
   mPrincipal = tempPrincipal;

   mRate = (mPeriodicRate * 12) * 100;
}

/***********************************************************************
 * Find m given p, i, n.
 * Finds the monthly payment
 **********************************************************************/
void Amortize::findMonthlyPayment()
{
   mMonthlyPayment = mPrincipal * (mPeriodicRate / (1 - pow(1 + mPeriodicRate, -mTermInMonths)));
}

/***********************************************************************
 * Find n given p, i, m.
 * Finds the size of the term in months
 **********************************************************************/
void Amortize::findTermInMonths()
{
   mTermInMonths = ((-log((mPrincipal - (mMonthlyPayment / mPeriodicRate)) /
                          (-mMonthlyPayment / mPeriodicRate)))/
                       (log(1 + mPeriodicRate))) + 0.5;
}

/*************************************************************************
 * Learned:
 * This function displays what I learned
 *************************************************************************/
void learned()
{
   cout << "What I learned. (Because of the Poe book you have in your office)\n\n"
        << "I decided to write a poem for this exploration\n"
        << "The title thereof was Clearness\n"
        << "I immediately knew I needed inspiration\n"
        << "So away I went, quite fearless\n"
        << "I started by reading the instructions\n"
        << "But, unfortunately, my ignorance became an obstruction\n"
        << "To Neff I went to get information\n"
        << "And as always, he gave me clarification\n\n";

   cout << "From equations to code I had to translate\n"
        << "Each was a challenge that made me think\n"
        << "The hardest by far was the interest rate\n"
        << "But from this challange I would not shrink\n"
        << "The rate could be found by a binary search\n"
        << "The solution I made with a little research\n"
        << "Alas! In my code bugs were mixed\n"
        << "But, with some work they were fixed\n\n";

   cout << "With a little collaboration I learned about 5.0\n"
        << "This was important to the legnth of the term\n"
        << "To avoid erroneous truncating we had to know,\n"
        << "about rounding correctly that the diff would confirm\n"
        << "By adding 5.0 it would assure\n"
        << "that we would get an answer secure\n"
        << "The lesson I learned caught me off guard\n"
        << "That coverting equations to code can be hard\n\n"; 

   cout << "Finally there was a connection mentioned by you\n"
        << "About recurrance relations in the amortization table\n"
        << "Monthly payments, interest, and principal too\n"
        << "Give a recurrance relation quite stable\n"
        << "I hope that this poem was successful\n"
        << "In showing the things I learned that were helpful\n"
        << "I sincerely hope you have a great day\n"
        << "And that you give me an excellent grade\n\n";

   cout << "--------------------------------------------\n\n";
}

/*************************************************************************
 * Usage:
 * Shows how to use this program
 *************************************************************************/
void usage(char* programName)
{
   cout << "Usage:\n\n"
        << "This program calculates, given 3 of the following, the fourth:\n"
        << "1. Principal or present value\n"
        << "2. APR - Annual Percentage Rate\n"
        << "3. Monthly Payment\n"
        << "4. Number of payments\n\n";
   
    cout << "Main reads command-line argument(s) as follows:\n"
 
         << "Name of a file containing parameter settings, or\n"
         << "(3 of the following 4 parameters are required)\n"
 
         << "p= principal (amount loaned)\n"
         << "n= term in months (number of payments)\n"
         << "r= annual interest rate (in percent, e.g. 3.75)\n"
         << "m= monthly payment amount\n"
 
         << "v= (optional) 1 = view amortization schedule\n"
         << "x= (optional) extra monthly payment\n"
         << "s= (optional) month extra payment starts\n"
         << "e= (optional) mont  h extra payment ends (default = n)\n";
}

// DO NOT CHANGE ANYTHING BELOW THIS LINE!

/****************************************************************
 * Check information for consistency:
 *
 * (E.g., the monthly payment as given should equal
 *  the monthly payment as calculated, and if
 *  the start month has been given but not the end month,
 *  set the end month to the term in months.
 *
 * Called after findAll() in run().
 ****************************************************************/
bool Amortize::checkConsistency()
{
   double monthlyPayment = mMonthlyPayment;
   // calculate monthly payment to make sure it's consistent,
   // as it could have just been given, but not yet calculated.
   findMonthlyPayment();
   if (abs(mMonthlyPayment - monthlyPayment) > 0.001)
   {
      // not close enough, we have a problem...
      return false;
   }
   else
   {
      if (mStart > 0 && mEnd == 0)
      {
         mEnd = mTermInMonths;
      }
      return true;
   }
}

/****************************************************************
 * Displays the month, interest paid, principal paid and balance.
 *
 * Called when displaying the amortization schedule.
 ****************************************************************/
void Amortize::showAmortizationLine(int month, double interestPaid,
                                    double principalPaid, double balance)
{
   cout << setw(5)  << month
        << setw(12) << interestPaid
        << setw(12) << principalPaid
        << setw(16) << balance
        << endl;
}

/****************************************************************
 * When the balance goes negative, correctly adjust the
 * principal paid and the total paid.
 *
 * Return true if the balance did go negative, false otherwise.
 *
 * Called when iterating through the amortization calculations.
 ****************************************************************/
bool Amortize::balanceGoesNegative(double balance, double &principalPaid,
                                   double &totalPaid)
{
   if (balance < 0)
   {
      principalPaid += balance;
      totalPaid += (mMonthlyPayment + balance);
      return true;
   }
   else
   {
      return false;
   }
}

/****************************************************************
 * Construct an Amortize instance.
 * Beaucoup parameters.
 ****************************************************************/
Amortize::Amortize(int termInMonths, double rate, double principal,
                   double monthlyPayment, double extraMonthlyPayment,
                   bool showAmortizationSchedule, int start, int end,
                   bool havePrincipal, bool haveRate,
                   bool haveTermInMonths, bool haveMonthlyPayment)
{
   mTermInMonths = termInMonths;
   mRate = rate;
   mPrincipal = principal;
   mMonthlyPayment = monthlyPayment;
   mExtraMonthlyPayment = extraMonthlyPayment;
   mShowAmortizationSchedule = showAmortizationSchedule;
   mStart = start;
   mEnd = end;
   mHavePrincipal = havePrincipal;
   mHavePeriodicRate = haveRate;
   mPeriodicRate = mRate * 0.01 * (1.0 / 12.0);
   mHaveTermInMonths = haveTermInMonths;
   mHaveMonthlyPayment = haveMonthlyPayment;
}

/****************************************************************
 * Conditionally runs with the data found (if consistent).
 * Reports an error if not found or inconsistent.
 ****************************************************************/
void Amortize::run()
{
   if (findAll() && checkConsistency())
   {
      display();
   }
   else
   {
      cerr << "Bad or missing information.\n";
   }
}

/****************************************************************
 * Find all missing parameters.
 ****************************************************************/
bool Amortize::findAll()
{
   if (!mHavePrincipal && mHaveMonthlyPayment &&
       mHavePeriodicRate && mHaveTermInMonths)
   {
      findPrincipal();
      mHavePrincipal = true;
   }
   if (!mHavePeriodicRate && mHavePrincipal &&
       mHaveMonthlyPayment && mHaveTermInMonths)
   {
      findPeriodicRate();
      mHavePeriodicRate = true;
   }
   if (!mHaveTermInMonths && mHavePrincipal &&
       mHaveMonthlyPayment && mHavePeriodicRate)
   {
      findTermInMonths();
      mHaveTermInMonths = true;
   }
   if (!mHaveMonthlyPayment && mHavePrincipal &&
       mHavePeriodicRate && mHaveTermInMonths)
   {
      findMonthlyPayment();
      mHaveMonthlyPayment = true;
   }

   return (mHavePrincipal && mHaveMonthlyPayment &&
           mHavePeriodicRate && mHaveTermInMonths);
}

/****************************************************************
 * Display the details of the principal, term, annual rate,
 * periodic rate, monthly payment, and extra payment (if any).
 *
 * Optionally display the amortization schedule.
 ****************************************************************/
void Amortize::display()
{
   double totalInterestPaid = 0.0;
   double totalPaid = 0.0;
   double totalExtra = 0.0;
   double totalSavings = 0.0;
   double balance = mPrincipal;
   cout << fixed << endl;
   cout << "##############################################\n\n";
   cout << "      Principal: " << setw(8) << setprecision(2) << mPrincipal
        << endl;
   cout << "           Term: " << mTermInMonths << " months\n";
   cout << "    Annual Rate: " << setprecision(3) << mRate << "%\n";
   cout << "  Periodic Rate: " << setprecision(7) << mPeriodicRate << endl;
   cout << endl;
   cout << "Monthly Payment: " << setw(8) << setprecision(2) << mMonthlyPayment
        << endl;
   if (mExtraMonthlyPayment > 0)
   {
      cout << "  Extra Payment: " << setw(8) << mExtraMonthlyPayment << endl;
   }
   cout << endl;
   if (mShowAmortizationSchedule)
   {
      cout << "Month     Interest   Principal       Balance\n";
   }
   int month;
   for (month = 1; month <= mTermInMonths; month++)
   {
      double interestPaid = balance * mPeriodicRate;
      totalInterestPaid += interestPaid;
      double principalPaid = mMonthlyPayment - interestPaid;
      balance -= principalPaid;

      if (balanceGoesNegative(balance, principalPaid, totalPaid))
      {
         if (mShowAmortizationSchedule)
         {
            showAmortizationLine(month, interestPaid, principalPaid, 0.0);
         }
         break;
      }

      totalPaid += mMonthlyPayment;

      if (month >= mStart && month <= mEnd)
      {
         balance -= mExtraMonthlyPayment;
         principalPaid += mExtraMonthlyPayment;
         totalExtra += mExtraMonthlyPayment;
      }
      if (mShowAmortizationSchedule)
      {
         showAmortizationLine(month, interestPaid, principalPaid, balance);
      }
   }

   if (mShowAmortizationSchedule)
   {
      cout << endl;
   }

   if (totalExtra > 0)
   {
      cout << "   Reduced Term: " << month << " months (shorter by "
           << (mTermInMonths - month) << " month(s) = "
           << (mTermInMonths - month) / 12 << " year(s) "
           << (mTermInMonths - month) % 12 << " month(s))\n";
   }

   cout << " Total Payments:" << setw(10) << totalPaid + totalExtra << endl;

   if (totalExtra > 0)
   {
      cout << " Extra Payments:" << setw(10) << totalExtra << endl;
   }

   cout << " Total Interest:" << setw(10)
        << totalInterestPaid << endl;

   if (totalExtra > 0)
   {
      totalSavings =
         ((mTermInMonths * mMonthlyPayment) - totalPaid - totalExtra);
      cout << "  Total Savings:" << setw(10)
           << totalSavings << endl;
   }

   cout << "  Intrst/Prncpl:" << setw(7)
        << (totalInterestPaid / mPrincipal * 100)
        << "%\n";
}

/*******************************************************************
 * runWithData is a global function declared in the clearnessCLI.cpp
 * file and implemented here.
 *
 * It serves as the interface between the CLI and the Amortize class.
 *** ****************************************************************/
void runWithData(int termInMonths, double rate, double principal,
                 double monthlyPayment, double extraMonthlyPayment,
                 bool showAmortizationSchedule, int start, int end,
                 bool havePrincipal, bool haveRate,
                 bool haveTermInMonths, bool haveMonthlyPayment)
{
   Amortize(termInMonths, rate, principal,
            monthlyPayment, extraMonthlyPayment,
            showAmortizationSchedule, start, end,
            havePrincipal, haveRate,
            haveTermInMonths, haveMonthlyPayment).run();
}
