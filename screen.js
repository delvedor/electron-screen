'use strict'

module.exports = function getInfo () {
  if (process.platform === 'win32') {
    return require('./build/Release/screen').getInfo
  } else {
    try {
      const screen = require('electron').screen
      return screen.getAllDisplays
    } catch (error) {
      throw new Error('Error: Cannot find module \'electron\'')
    }
  }
}
