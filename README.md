# Predicting the Semantic Orientation of Communication over Social Networking.

> The World needs a particular channel through which any post, message, tweet or comment is scrutinized before being broadcasted.

## Abstract
Developing a state of the art sentiment analysis system that detects the sentiment of short
messages/posts/etc such as tweets, facebook activity like SMS (message-level task) or posting or commenting and many other. The sentiment of a word or a phrase within a message (term-level task). The system is based on a supervised
statistical text classification approach leveraging a variety of surface form, semantic, and
sentiment features. The sentiment features are primarily derived from large datasets sentiment lexicons. These lexicons are explitcitply collecting from cyberspace. Sentiment word hashtags or simple words on facebook instagram or many other social media with emoticons. To adequately capture the sentiment of words in negated contexts, a separate sentiment lexicon is generated for negated words.

## Derived Classifier.

Naive Baye's (NB) classifier by Observing [Baye's’](https://en.wikipedia.org/wiki/Naive_Bayes_classifier) rule,
  P(c | d) = P(c)P(d | c)/P(d).
  
 ## System Requirement
 
 * Hardware Requirements:
    * Processor: Intel(R) Core(TM)2 Quad CPU Q8400 @ 2.66GHz
    * RAM : 2GB (Operating System + sofware)
    * HardDisk : 1GB (Data sets)

 * Software Requirements:
    * [Linux Operating System](https://www.linux.org/) (Recommended) <img src="https://vpnpick.com/wp-content/uploads/2015/12/2000px-Tux.svg_.png" alt="Drawing" width = 40px height = 40px />
    * [GCC](https://gcc.gnu.org/) (GNU Compiler Collection) <img src="http://www.cse.iitb.ac.in/grc/images/gcc-logo.gif" alt="Drawing" width = 40px height = 40px />
    * [GTK](https://www.gtk.org/) (GIMP Tool Kit) <img src="https://upload.wikimedia.org/wikipedia/commons/3/30/GTK.png" alt="Drawing" width = 40px height = 40px />
    * [GLADE](https://glade.gnome.org/) (A User Interface Designer) <img src="https://fossies.org/linux/glade/data/icons/hicolor/256x256/apps/glade.png" alt="Drawing" width = 40px height = 40px />
    
## Compilation & Execution:

```sh
$ sudo apt-get install libgtk-3-dev
$ gcc -o <output-file-name> <code-file-extension.c> -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
$ ./<output-file-name>
```
## BlackBok Functioning:

Enter some text (Post, message, comment,tweet or anything), the software predicts the the sentiment of the respective text.

## Datasets Collection :

1. [Mendeley Datasets](https://www.mendeley.com/datasets): A collection of millions of data as per the sentiments for Hindi and English.
2. [MT](http://www.manythings.org/sentences/words/): A great collection of sentences with the respective words.
3. [Stanford datasets](http://ai.stanford.edu/~amaas/data/sentiment/) : This is a dataset for binary sentiment classification containing substantially more data than previous benchmark datasets. We provide a set of 25,000 highly polar movie reviews for training, and 25,000 for testing. There is additional unlabeled data for use as well. Raw text and already processed bag of words formats are provided. See the README file contained in the release for more details.

## Contribution:

1. Fork the Repository.
2. Clone the project to your machine.
3. Add respective and relevent data to it and upload as a new branch to it.
4. Add your name and Profile address to below named Developer and Contributors

## Developers and Contributors:

1. [Harshal Mittal](https://twitter.com/Harshal306)
2. [Shubhangi Srivastava]
3. [Mansi Sahu]
