module.exports = {
    apps : [
      {
        name: 'proton-bots',
        script: 'dist/index.js',
        node_args : '-r dotenv/config',
        watch: false,
        env: {
          'CHAIN': 'proton'
        }
      }
    ]
};