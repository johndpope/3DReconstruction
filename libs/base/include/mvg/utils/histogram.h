﻿#ifndef MVG_UTILS_HISTOGRAM_H_
#define MVG_UTILS_HISTOGRAM_H_

#include <iomanip>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>


namespace mvg{
// A histogram class.
// The Histogram object can keep a tally of values
// within a range, the range is arranged into some
// number of bins specified during construction.
// Any allocation of a Histogram object may throw
// a bad_alloc exception.
// Dedicated to the public domain.
// Jansson Consulting
// 2009-06-30, updated 2011-06-17 and 2011-08-03

// 2011-12-17 Modified by Pierre Moulon
//  - use vector array to avoid memory managment
//  - add value by sequence with iterator
	namespace utils{

		template <typename T>
		class Histogram
		{
		public:
			// Construct a histogram that can count
			// within a range of values.
			// All bins of the histogram are set to zero.
			Histogram(
				const T& Start = T(0),
				const T& End = T(0),
				const size_t& nBins = 10) :
				Start(Start),
				End(End),
				nBins_by_interval(nBins / (End - Start)),
				nBins(nBins),
				overflow(0),
				underflow(0)
			{
				freq.resize(nBins, 0);
			}

			// Construct a histogram from a sequence of data
			template <typename DataInputIterator>
			void Add(DataInputIterator begin, DataInputIterator end)
			{
				for (DataInputIterator iter = begin; iter != end; ++iter)
					Add(static_cast<T>(*iter));
			}

			// Increase the count for the bin that holds a
			// value that is in range for this histogram or
			// the under-/overflow count if it is not in range.
			void Add(const T& x)
			{
				if (x < Start)
					++underflow;
				else
				{
					const size_t i(
						static_cast<size_t>(
						(x - Start)*nBins_by_interval));
					if (i < nBins) ++freq[i];
					else ++overflow;
				}
			}
			// Get the sum of all counts in the histogram.
			size_t GetTotalCount() const
			{
				return std::accumulate(freq.begin(), freq.end(), 0.0);
			}
			// Get the overflow count.
			size_t GetOverflow() const
			{
				return overflow;
			}
			// Get the underflow count.
			size_t GetUnderflow() const
			{
				return underflow;
			}
			// Get frequencies
			const std::vector<size_t> & GetHist() const { return freq; }
			// Get XbinsValue
			std::vector<T> GetXbinsValue() const {
				std::vector<T> vec_XbinValue(nBins, T(0));
				double val = (End - Start) / static_cast<double>(nBins - 1);
				for (size_t i = 0; i < nBins; ++i)
					vec_XbinValue[i] = (val*static_cast<double>(i)+Start);
				return vec_XbinValue;
			}
			// Get start
			const double GetStart() const { return Start; }
			// Get End
			const double GetEnd() const { return End; }

			// Text display of the histogram
			std::string ToString(const std::string & sTitle = "") const
			{
				std::ostringstream os;
				os << std::endl << sTitle << std::endl;
				const size_t n = freq.size();
				for (size_t i = 0; i < n; ++i)
				{
					os << std::setprecision(3)
						<< static_cast<float>(End - Start) / n*static_cast<float>(i)
						<< "\t|\t" << freq[i] << "\n";
				}
				os << std::setprecision(3) << End << std::endl;
				return os.str();
			}

		private:
			double Start, End, nBins_by_interval;
			size_t nBins; // number of bins
			std::vector<size_t> freq; // histogram
			size_t overflow, underflow; //count under/over flow
		};
	}// namespace utils
} // namespace mvg

#endif // MVG_UTILS_HISTOGRAM_H_
