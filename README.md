# Electron Screen
[![js-standard-style](https://img.shields.io/badge/code%20style-standard-brightgreen.svg?style=flat)](http://standardjs.com/)

Small Module that returns an array with all the monitors connected to the pc with their resolution and position.  
The standard API of electron already do this, but under Windows the screen api suffers lot of issues.

**Works only under Windows OS!**  
If you want to manage screens with other OS have a look [here](https://github.com/electron/electron/blob/master/docs/api/screen.md).

## Usage
Download and install `electron-screen` through npm, then require it:
```javascript
const screen = require('electron-screen')()

console.log(screen())
```
Under **Windows** `electron-screen` returns the following object:
```javascript
{
  bounds: {
    x: Number,
    y: Number,
    width: Number,
    height: Number
  }
}
```

## Build
```
$ npm build .
```

## Contributing
If you feel you can help in any way, be it with examples, extra testing, or new features please open a pull request or open an issue.

I would make a special thanks to [@Corralx](https://github.com/Corralx) for helping me to improving the code.

The code follows the Standard code style.  
[![js-standard-style](https://cdn.rawgit.com/feross/standard/master/badge.svg)](https://github.com/feross/standard)

______________________________________________________________________________________________________________________
## License
The code is released under the MIT license.

The software is provided "as is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose and non infringement. In no event shall the authors or copyright holders be liable for any claim, damages or other liability, whether in an action of contract, tort or otherwise, arising from, out of or in connection with the software or the use or other dealings in the software.
