'use strict'

/*
 * Project: electron-screen
 * Version: 1.0.1
 * Author: delvedor
 * Twitter: @delvedor
 * License: MIT
 * GitHub: https://github.com/delvedor/electron-screen
 */

function getScreenInfo () {
  if (process.platform === 'win32') {
    const screen = require('./build/Release/electronscreen').getInfo
    return screen
  } else {
    throw new Error('electron-screen works only under Windows OS.')
  }
}

module.exports = getScreenInfo
